#include "Emitter.h"

/* TODO - Discern between normal number from big numbers */

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

#define emit_nil()   OA(OP_STOZK, CONST(MARG_NIL))
#define emit_false() OA(OP_STOZK, CONST(MARG_FALSE))
#define emit_true()  OA(OP_STOZK, CONST(MARG_TRUE))

#define emit_self()  OA(OP_STOZI, INSTANCE("@self"))
#define emit_super() OA(OP_STOZI, INSTANCE("@super"))

#define emit_integer()                              \
  ptrdiff_t int_value;                              \
  sscanf(formal_bytecode[++ip], "%td", &int_value); \
  OA(OP_STOZK, CONST(MARG_INTEGER(int_value)))
#define emit_float()                                  \
  double float_value;                                 \
  sscanf(formal_bytecode[++ip], "%lf", &float_value); \
  OA(OP_STOZK, CONST(MARG_FLOAT(float_value)))

#define emit_string() OA(OP_STOZK, CONST(MARG_STRING(formal_bytecode[++ip])))
#define emit_label_local() \
  ip++;                    \
  COMP_LABEL_LOCAL(formal_bytecode[ip])
#define emit_label_instance() \
  ip++;                       \
  COMP_LABEL_INSTANCE(formal_bytecode[ip])
#define emit_label_global() \
  ip++;                     \
  COMP_LABEL_GLOBAL(formal_bytecode[ip])
#define emit_symbol() OA(OP_STOZK, CONST(MARG_SYMBOL(formal_bytecode[++ip])))

#define emit_enumerable_new()                                  \
  do {                                                         \
    size_t number_of_elements;                                 \
    sscanf(formal_bytecode[++ip], "%zu", &number_of_elements); \
    OAB(                                                       \
      OP_PRIM,                                                 \
      CONST(MARG_STRING("__PRIM_NEW:")),                       \
      CONST(MARG_INTEGER(number_of_elements))                  \
    );                                                         \
  } while(0)

#define emit_global()   OA(OP_STOZG, GLOBAL(formal_bytecode[++ip]))
#define emit_instance() OA(OP_STOZI, INSTANCE(formal_bytecode[++ip]))
#define emit_local()    OA(OP_STOZL, LOCAL(formal_bytecode[++ip]))

VM *emitter_emit(VM *vm) {
  size_t ip;
  char **formal_bytecode = vm->formal_bytecode;
  size_t bytecode_size   = vector_size(formal_bytecode);

  if(vm->error) {
    goto exit;
  }

  for(ip = 0; ip < bytecode_size; ip++) {
    char *fmcode = formal_bytecode[ip];

    switch_fmcode(FM_NIL) { emit_nil(); }
    case_fmcode(FM_FALSE) { emit_false(); }
    case_fmcode(FM_TRUE) { emit_true(); }

    case_fmcode(FM_SELF) { emit_self(); }
    case_fmcode(FM_SUPER) { emit_super(); }

    case_fmcode(FM_INTEGER) { emit_integer(); }
    case_fmcode(FM_FLOAT) { emit_float(); }

    case_fmcode(FM_STRING) { emit_string(); }
    case_fmcode(FM_LABEL_LOCAL) { emit_label_local(); }
    case_fmcode(FM_LABEL_INSTANCE) { emit_label_instance(); }
    case_fmcode(FM_LABEL_GLOBAL) { emit_label_global(); }
    case_fmcode(FM_SYMBOL) { emit_symbol(); }

    case_fmcode(FM_TENSOR) {
      OA(OP_STOZG, GLOBAL("$Tensor"));
      emit_enumerable_new();
    }
    case_fmcode(FM_TUPLE) {
      OA(OP_STOZG, GLOBAL("$Tuple"));
      emit_enumerable_new();
    }
    case_fmcode(FM_TABLE) {
      OA(OP_STOZG, GLOBAL("$Table"));
      emit_enumerable_new();
    }
    case_fmcode(FM_BITSTRING) {
      OA(OP_STOZG, GLOBAL("$Bitstring"));
      emit_enumerable_new();
    }

    case_fmcode(FM_GLOBAL) { emit_global(); }
    case_fmcode(FM_INSTANCE) { emit_instance(); }
    case_fmcode(FM_LOCAL) { emit_local(); }

    case_fmcode(FM_METHOD_START) {
      /* MargValue new_method = MARG_METHOD(
        vm->current->bound_method, formal_bytecode[++ip]
      );
      emit_variable_length(OP_OBJECT);
      emit_temporary(new_method);
      vm->current = AS_METHOD(new_method)->proc; */
    }
    case_fmcode(FM_METHOD_END) {
      /* TODO - Call OP_EXACTREC */
      /* emit_byte(OP_EXIT_ACTIVATION_RECORD);
      vm->current = vm->current->bound_proc; */
    }
    case_fmcode(FM_METHOD_ANY_OBJECT) { /* TODO - Empty?? */ }
    case_fmcode(FM_METHOD_RECEIVER) {
      /* TODO - goto the beginning with formal_bytecode[ip + 1] and read the
       * next fmcode pair (like FM_LOCAL, a) and add to method properties */
      (void)formal_bytecode[++ip];
      (void)formal_bytecode[++ip];
    }
    case_fmcode(FM_METHOD_PARAMETER) {
      /* TODO - Similar to receiver */
      (void)formal_bytecode[++ip];
      (void)formal_bytecode[++ip];
    }
    case_fmcode(FM_METHOD_NAME) {
      char *method_name = formal_bytecode[++ip];
      /* TODO - Add to method properties */
      (void)method_name;
    }

    case_fmcode(FM_ASSIGNMENT) {
      char *assignment_name = formal_bytecode[++ip];
      /* emit_byte(OP_1);
      emit_variable_length(OP_SEND);
      emit_temporary(MARG_STRING(assignment_name)); */
      (void)assignment_name;
    }
    case_fmcode(FM_SUBSCRIPT) {
      char *subscript_name = formal_bytecode[++ip];
      /* emit_byte(OP_1);
      emit_variable_length(OP_SEND);
      emit_temporary(MARG_STRING(subscript_name)); */
      (void)subscript_name;
    }
    case_fmcode(FM_LHS) {
      char *lhs_name = formal_bytecode[++ip];
      /* emit_byte(OP_1);
      emit_variable_length(OP_SEND);
      emit_temporary(MARG_STRING(lhs_name)); */
      (void)lhs_name;
    }
    case_fmcode(FM_UNARY) {
      char *message_name = formal_bytecode[++ip];
      /* emit_byte(OP_1);
      emit_variable_length(OP_SEND);
      emit_temporary(MARG_STRING(unary_name)); */
      (void)message_name;
    }
    case_fmcode(FM_BINARY) {
      char *message_name = formal_bytecode[++ip];
      /* emit_byte(OP_1);
      emit_variable_length(OP_SEND);
      emit_temporary(MARG_STRING(binary_name)); */
      (void)message_name;
    }
    case_fmcode(FM_KEYWORD) {
      char *message_name         = formal_bytecode[++ip];
      char *number_of_parameters = formal_bytecode[++ip];

      switch_message_case("__PRIM_PUTS:") { /* emit_byte(OP_PUTS); */ }
      message_case("__PRIM_INCLUDE:") { /* emit_byte(OP_INCLUDE); */ }
      /* message_case("...") { ... } */
      message_default {
        (void)number_of_parameters;
        /* emit_variable_length(OP_OBJECT);
        emit_temporary(MARG_INTEGER(number_of_parameters)); */

        /* emit_variable_length(OP_SEND);
        emit_temporary(MARG_STRING(message_name)); */
      }
    }
  }

  OP(OP_HALT);

exit:
  vm_free_formal_bytecode();
  return vm;
}
