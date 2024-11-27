#include "Emitter.h"

/* TODO - Discern between normal number from big numbers */

#include "../opcode/fmcodes.h"
#include "../opcode/instruction.h"
#include "../opcode/opcodes.h"

#define switch_fmcode(opstr) if(string_equals(fmcode, opstr))
#define case_fmcode(opstr)   else if(string_equals(fmcode, opstr))

#define switch_message_case(message) if(string_equals(message_name, message))
#define message_case(message)        else if(string_equals(message_name, message))
#define message_default              else

#define emit_label_local() \
  ip++;                    \
  COMP_LABEL_LOCAL(formal_bytecode[ip])
#define emit_label_instance() \
  ip++;                       \
  COMP_LABEL_INSTANCE(formal_bytecode[ip])
#define emit_label_global() \
  ip++;                     \
  COMP_LABEL_GLOBAL(formal_bytecode[ip])
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
    case_fmcode(FM_SYMBOL) {
      OA(OP_STOZK, CONST(MARG_SYMBOL(formal_bytecode[++ip])));
    }
    case_fmcode(FM_LABEL_LOCAL) { emit_label_local(); }
    case_fmcode(FM_LABEL_INSTANCE) { emit_label_instance(); }
    case_fmcode(FM_LABEL_GLOBAL) { emit_label_global(); }

    case_fmcode(FM_TENSOR) {
      size_t i;
      MargValue t_value = MARG_TENSOR();
      MargTensor *t_obj = AS_TENSOR(t_value);
      size_t number_of_elements;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_elements);
      for(i = 1; i <= number_of_elements; i++) {
        marg_tensor_add(t_obj, K(-i));
      }
      OA(OP_STOZK, CONST(t_value));
    }
    case_fmcode(FM_TUPLE) {
      size_t i;
      MargValue t_value = MARG_TUPLE();
      MargTuple *t_obj  = AS_TUPLE(t_value);
      size_t number_of_elements;
      sscanf(formal_bytecode[++ip], "%zu", &number_of_elements);
      for(i = 1; i <= number_of_elements; i++) {
        marg_tuple_add(t_obj, K(-i));
      }
    }
    case_fmcode(FM_BITSTRING) {
      char *number_of_bits = formal_bytecode[++ip];
      /* emit_variable_length(OP_BITSTRING);
      emit_temporary(number_of_bits); */
      (void)number_of_bits;
    }
    case_fmcode(FM_TABLE) {
      char *number_of_pairs = formal_bytecode[++ip];
      /* emit_variable_length(OP_TABLE);
      emit_temporary(number_of_pairs); */
      (void)number_of_pairs;
    }

    case_fmcode(FM_GLOBAL) { OA(OP_STOZG, GLOBAL(formal_bytecode[++ip])); }
    case_fmcode(FM_INSTANCE) { OA(OP_STOZI, INSTANCE(formal_bytecode[++ip])); }
    case_fmcode(FM_LOCAL) { OA(OP_STOZL, LOCAL(formal_bytecode[++ip])); }

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

      switch_message_case("call") { /* emit_byte(OP_PROC_CALL); */ }
      message_default{
        /* emit_byte(OP_1);
        emit_variable_length(OP_SEND);
        emit_temporary(MARG_STRING(unary_name)); */
      }

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

      switch_message_case("puts:") { /* emit_byte(OP_PUTS); */ }
      message_case("include:") { /* emit_byte(OP_INCLUDE); */ }
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
