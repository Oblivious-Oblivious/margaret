#include "Emitter.h"

/* TODO - Discern between normal numbers and big numbers */

#include "../opcode/fmcodes.h"
#include "../opcode/instruction.h"
#include "../opcode/opcodes.h"

#include <stdio.h> /* sscanf */

#define switch_fmcode(opstr) if(string_equals(fmcode, opstr))
#define case_fmcode(opstr)   else if(string_equals(fmcode, opstr))

#define switch_message_case(message) if(string_equals(message_name, message))
#define message_case(message)        else if(string_equals(message_name, message))
#define message_default              else

#define COMP_LABEL_LOCAL(name) \
  (SET_L(LOCAL(name), MARG_LABEL(name)), OA(OP_STOZL, LOCAL(name)))
#define COMP_LABEL_INSTANCE(name) \
  (SET_I(INSTANCE(name), MARG_LABEL(name)), OA(OP_STOZI, INSTANCE(name)))
#define COMP_LABEL_GLOBAL(name) \
  (SET_G(GLOBAL(name), MARG_LABEL(name)), OA(OP_STOZG, GLOBAL(name)))

#define prim_helper(number_of_parameters)     \
  OAB(                                        \
    OP_PRIM,                                  \
    CONST(MARG_STRING(message_name)),         \
    CONST(MARG_INTEGER(number_of_parameters)) \
  )

VM *emitter_emit(VM *vm) {
  size_t ip;
  char **formal_bytecode = vm->formal_bytecode;
  size_t bytecode_size   = vector_size(formal_bytecode);

  if(vm->error) {
    goto exit;
  }

  for(ip = 0; ip < bytecode_size; ip++) {
    char *fmcode = formal_bytecode[ip];

    switch_fmcode(FM_NIL) { OA(OP_STOZK, CONST(MARG_NIL)); }
    case_fmcode(FM_FALSE) { OA(OP_STOZK, CONST(MARG_FALSE)); }
    case_fmcode(FM_TRUE) { OA(OP_STOZK, CONST(MARG_TRUE)); }

    case_fmcode(FM_SELF) { OA(OP_STOZI, INSTANCE("@self")); }
    case_fmcode(FM_SUPER) { OA(OP_STOZI, INSTANCE("@super")); }

    case_fmcode(FM_INTEGER) {
      ptrdiff_t int_value;
      sscanf(formal_bytecode[++ip], "%td", &int_value);
      OA(OP_STOZK, CONST(MARG_INTEGER(int_value)));
    }
    case_fmcode(FM_FLOAT) {
      double float_value;
      sscanf(formal_bytecode[++ip], "%lf", &float_value);
      OA(OP_STOZK, CONST(MARG_FLOAT(float_value)));
    }

    case_fmcode(FM_STRING) {
      OA(OP_STOZK, CONST(MARG_STRING(formal_bytecode[++ip])));
    }
    case_fmcode(FM_LABEL_LOCAL) {
      ip++;
      COMP_LABEL_LOCAL(formal_bytecode[ip]);
    }
    case_fmcode(FM_LABEL_INSTANCE) {
      ip++;
      COMP_LABEL_INSTANCE(formal_bytecode[ip]);
    }
    case_fmcode(FM_LABEL_GLOBAL) {
      ip++;
      COMP_LABEL_GLOBAL(formal_bytecode[ip]);
    }
    case_fmcode(FM_SYMBOL) {
      OA(OP_STOZK, CONST(MARG_SYMBOL(formal_bytecode[++ip])));
    }

    case_fmcode(FM_TENSOR) {
      size_t number_of_elements;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_elements);
      OA(OP_TENSOR, CONST(MARG_INTEGER(number_of_elements)));
    }
    case_fmcode(FM_TUPLE) {
      size_t number_of_elements;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_elements);
      OA(OP_TUPLE, CONST(MARG_INTEGER(number_of_elements)));
    }
    case_fmcode(FM_TABLE) {
      size_t number_of_elements;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_elements);
      OA(OP_TABLE, CONST(MARG_INTEGER(number_of_elements)));
    }
    case_fmcode(FM_BITSTRING) {
      size_t number_of_elements;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_elements);
      OA(OP_BITSTRING, CONST(MARG_INTEGER(number_of_elements)));
    }

    case_fmcode(FM_GLOBAL) { OA(OP_STOZG, GLOBAL(formal_bytecode[++ip])); }
    case_fmcode(FM_INSTANCE) { OA(OP_STOZI, INSTANCE(formal_bytecode[++ip])); }
    case_fmcode(FM_LOCAL) { OA(OP_STOZL, LOCAL(formal_bytecode[++ip])); }

    case_fmcode(FM_POP) { OP(OP_POP); }

    case_fmcode(FM_METHOD_START) {
      vm->current =
        AS_METHOD(MARG_METHOD(vm->current->bound_object, vm->current, NULL));
    }
    case_fmcode(FM_METHOD_END) {
      MargValue new_method = QNAN_BOX(vm->current);
      OP(OP_EXACTREC);
      vm->current = vm->current->bound_method;
      OA(OP_STOZK, CONST(new_method));
    }
    case_fmcode(FM_METHOD_ARGUMENT) {
      vector_add(
        vm->current->argument_names, string_new(formal_bytecode[++ip])
      );
    }
    case_fmcode(FM_METHOD_NAME) {
      vm->current->message_name = string_new(formal_bytecode[++ip]);
    }

    case_fmcode(FM_ASSIGNMENT) { OP(OP_ASSIGN); }
    case_fmcode(FM_SUBSCRIPT) {
      OAB(
        OP_SEND, CONST(MARG_STRING(string_new("[]"))), CONST(MARG_INTEGER(1))
      );
    }
    case_fmcode(FM_LHS) {
      OAB(
        OP_SEND,
        CONST(MARG_STRING(string_new(formal_bytecode[++ip]))),
        CONST(MARG_INTEGER(0))
      );
    }
    case_fmcode(FM_UNARY) {
      OAB(
        OP_SEND,
        CONST(MARG_STRING(string_new(formal_bytecode[++ip]))),
        CONST(MARG_INTEGER(0))
      );
    }
    case_fmcode(FM_BINARY) {
      OAB(
        OP_SEND,
        CONST(MARG_STRING(string_new(formal_bytecode[++ip]))),
        CONST(MARG_INTEGER(1))
      );
    }
    case_fmcode(FM_KEYWORD) {
      char *message_name = string_new(formal_bytecode[++ip]);
      size_t number_of_parameters;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_parameters);

      switch_message_case("MARGARET_INSPECT:") { prim_helper(1); }
      message_case("MARGARET_BIND:TO:") { prim_helper(2); }
      message_case("MARGARET_MESSAGES:") { prim_helper(1); }
      /* message_case("MARGARET_RAISE:") { prim_helper(0); } */

      message_case("NUMERIC_ADD:WITH:") { prim_helper(2); }
      message_case("NUMERIC_SUB:WITH:") { prim_helper(2); }
      message_case("NUMERIC_MUL:WITH:") { prim_helper(2); }
      message_case("NUMERIC_DIV:WITH:") { prim_helper(2); }

      message_case("STRING_ADD:STR:") { prim_helper(2); }
      message_case("STRING_SIZE:") { prim_helper(1); }
      message_case("STRING_SHORTEN:TO:") { prim_helper(2); }
      message_case("STRING_SKIP_FIRST:CHARS:") { prim_helper(2); }
      message_case("STRING_IGNORE_LAST:CHARS:") { prim_helper(2); }
      message_case("STRING_DELETE:") { prim_helper(1); }
      message_case("STRING_REMOVE:CHAR:") { prim_helper(2); }
      message_case("STRING_EQUALS:OTHER:") { prim_helper(2); }

      message_case("TENSOR_ADD:ELEMENT:") { prim_helper(2); }
      message_case("TENSOR_ADD:TENSOR:") { prim_helper(2); }
      message_case("TENSOR_REMOVE:ELEMENT:") { prim_helper(2); }
      message_case("TENSOR_REMOVE_LAST:") { prim_helper(1); }
      message_case("TENSOR_LAST:") { prim_helper(1); }
      message_case("TENSOR_SIZE:") { prim_helper(1); }

      message_case("TUPLE_ADD:ELEMENT:") { prim_helper(2); }
      message_case("TUPLE_SIZE:") { prim_helper(1); }

      message_case("TABLE_ADD:KEY:VALUE:") { prim_helper(3); }
      message_case("TABLE_GET:KEY:") { prim_helper(2); }
      message_case("TABLE_REMOVE:KEY:") { prim_helper(2); }
      message_case("TABLE_SIZE:") { prim_helper(1); }

      message_case("BITSTRING_ADD:VALUE:BITS:") { prim_helper(3); }
      message_case("BITSTRING_SIZE:") { prim_helper(1); }
      message_default {
        OAB(
          OP_SEND,
          CONST(MARG_STRING(message_name)),
          CONST(MARG_INTEGER(number_of_parameters))
        );
      }
    }
  }

  OP(OP_HALT);

exit:
  return vm;
}
