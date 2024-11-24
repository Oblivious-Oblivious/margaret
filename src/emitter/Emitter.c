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

VM *emitter_emit(VM *vm) {
  size_t ip;
  char **formal_bytecode = vm->formal_bytecode;
  size_t bytecode_size   = vector_size(formal_bytecode);

  if(vm->error) {
    goto exit;
  }

  for(ip = 0; ip < bytecode_size; ip++) {
    char *fmcode = formal_bytecode[ip];

    switch_fmcode(FM_NIL) { /* emit_byte(OP_NIL); */ }
    case_fmcode(FM_FALSE) { /* emit_byte(OP_FALSE); */ }
    case_fmcode(FM_TRUE) { /* emit_byte(OP_TRUE); */ }

    case_fmcode(FM_SELF) { /* emit_byte(OP_SELF); */ }
    case_fmcode(FM_SUPER) { /* emit_byte(OP_SUPER); */ }

    case_fmcode(FM_INTEGER) {
      char *temp_int_value = formal_bytecode[++ip];
      /* emit_variable_length(OP_OBJECT);
      emit_temporary(temp_int_value); */
      (void)temp_int_value;
    }
    case_fmcode(FM_FLOAT) {
      char *temp_float_value = formal_bytecode[++ip];
      /* emit_variable_length(OP_OBJECT);
      emit_temporary(temp_float_value); */
      (void)temp_float_value;
    }

    case_fmcode(FM_STRING) {
      char *temp_string_value = formal_bytecode[++ip];
      /* emit_variable_length(OP_OBJECT); */
      (void)temp_string_value;
    }
    case_fmcode(FM_LABEL) {
      char *temp_label_value = formal_bytecode[++ip];
      /* emit_variable_length(OP_OBJECT);
      emit_temporary(temp_label_value); */
      (void)temp_label_value;
    }
    case_fmcode(FM_SYMBOL) {
      char *temp_symbol_value = formal_bytecode[++ip];
      /* emit_variable_length(OP_OBJECT);
      emit_temporary(temp_symbol_value); */
      (void)temp_symbol_value;
    }

    case_fmcode(FM_TENSOR) {
      char *number_of_elements = formal_bytecode[++ip];
      /* emit_variable_length(OP_TENSOR);
      emit_temporary(number_of_elements); */
      (void)number_of_elements;
    }
    case_fmcode(FM_TUPLE) {
      char *number_of_elements = formal_bytecode[++ip];
      /* emit_variable_length(OP_TUPLE);
      emit_temporary(number_of_elements); */
      (void)number_of_elements;
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

    case_fmcode(FM_GLOBAL) {
      char *variable_name = formal_bytecode[++ip];
      /* emit_variable_length(OP_GLOBAL);
      emit_temporary(variable_name); */
      (void)variable_name;
    }
    case_fmcode(FM_INSTANCE) {
      char *variable_name = formal_bytecode[++ip];
      /* emit_variable_length(OP_INSTANCE);
      emit_temporary(variable_name); */
      (void)variable_name;
    }
    case_fmcode(FM_LOCAL) {
      char *variable_name = formal_bytecode[++ip];
      /* emit_variable_length(OP_LOCAL);
      emit_temporary(variable_name); */
      (void)variable_name;
    }

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

  vector_add(vm->current->bytecode, OP_HALT);

exit:
  vm_free_formal_bytecode();
  return vm;
}
