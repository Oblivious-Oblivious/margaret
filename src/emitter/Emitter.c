#include "Emitter.h"

/* TODO - Discern between normal number from big numbers */

/* #include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../inspector/Inspector.h"
#include "../opcode/fmcodes.h"
#include "../opcode/MargValue.h"
#include "../opcode/opcodes.h"

#define switch_fmcode_case(opstr) if(string_equals(fmcode, opstr))
#define fmcode_case(opstr)        else if(string_equals(fmcode, opstr))

#define switch_unary_case(unarystr) \
  if(string_equals(unary_name, string_new(unarystr)))
#define unary_case(unarystr) \
  else if(string_equals(unary_name, string_new(unarystr)))
#define default_unary_case else

#define switch_binary_case(binarystr) \
  if(string_equals(binary_name, string_new(binarystr)))
#define binary_case(binarystr) \
  else if(string_equals(binary_name, string_new(binarystr)))
#define default_binary_case else

#define switch_keyword_case(keywordstr) \
  if(string_equals(keyword_name, string_new(keywordstr)))
#define keyword_case(keywordstr) \
  else if(string_equals(keyword_name, string_new(keywordstr)))
#define default_keyword_case else

#define emit_byte(byte)           vector_add(vm->current->bytecode, byte)
#define emit_bytes2(byte1, byte2) (emit_byte(byte1), emit_byte(byte2))
#define emit_bytes3(byte1, byte2, byte3) \
  (emit_byte(byte1), emit_byte(byte2), emit_byte(byte3))
#define emit_bytes4(byte1, byte2, byte3, byte4) \
  (emit_byte(byte1), emit_byte(byte2), emit_byte(byte3), emit_byte(byte4))

#define emit_variable_length_op(opcode)                     \
  do {                                                      \
    if(vector_size(vm->current->bytecode) < 256) {          \
      vector_add(vm->current->bytecode, (opcode));          \
    } else if(vector_size(vm->current->bytecode) < 65536) { \
      vector_add(vm->current->bytecode, (opcode##_WORD));   \
    } else {                                                \
      vector_add(vm->current->bytecode, (opcode##_DWORD));  \
    }                                                       \
  } while(0)

#define emit_temporary(temporary)                    \
  do {                                               \
    uint32_t temporary_index;                        \
    make_temporary(vm, temporary, &temporary_index); \
    add_temporary(vm, temporary_index);              \
  } while(0)

#define make_temporary(vm, temporary, index)         \
  vector_add((vm)->current->constants, temporary); \
  *(index) = vector_size((vm)->current->constants) - 1;

#define add_temporary(vm, temporary_index) \
  _add_temporary_function((vm), (temporary_index), 256 + 1, 65536 + 1);
#define add_premade_temporary(vm, temporary_index) \
  _add_temporary_function((vm), (temporary_index), 256, 65536);

static void _add_temporary_function(
  VM *vm, uint32_t temporary_index, uint16_t byte_bound, uint32_t word_bound
) {
  if(vector_size(vm->current->bytecode) < byte_bound) {
    emit_byte((uint8_t)temporary_index);
  } else if(vector_size(vm->current->bytecode) < word_bound) {
    uint8_t temporary_index_in_bytes[2];
    word_to_bytes(temporary_index, temporary_index_in_bytes);
    emit_bytes2(temporary_index_in_bytes[0], temporary_index_in_bytes[1]);
  } else {
    uint8_t temporary_index_in_bytes[4];
    dword_to_bytes(temporary_index, temporary_index_in_bytes);
    emit_bytes4(
      temporary_index_in_bytes[0],
      temporary_index_in_bytes[1],
      temporary_index_in_bytes[2],
      temporary_index_in_bytes[3]
    );
  }
}

VM *emitter_emit(VM *vm) {
  size_t ip;
  char **formal_bytecode  = vm->formal_bytecode;
  size_t bytecode_size    = vector_size(formal_bytecode);
  MargObject *marg_object = NULL;
  MargMethod *main_method = NULL;

  if(vm->error) {
    return vm;
  }

  marg_object = AS_OBJECT(table_get(&vm->global_variables, "$Margaret"));
  main_method = AS_METHOD(table_get(&marg_object->messages, ""));

  vm->current->bytecode = NULL;
  vm->current           = main_method->proc;

  for(ip = 0; ip < bytecode_size; ip++) {
    char *fmcode = formal_bytecode[ip];

    switch_fmcode_case(FM_LOCAL) {
      char *variable_name = formal_bytecode[++ip];
      MargValue temporary = MARG_STRING(variable_name);
      emit_variable_length_op(OP_GET_LOCAL);
      emit_temporary(temporary);
    }
    fmcode_case(FM_INSTANCE) {
      char *variable_name = formal_bytecode[++ip];
      MargValue temporary = MARG_STRING(variable_name);
      emit_variable_length_op(OP_GET_INSTANCE);
      emit_temporary(temporary);
    }
    fmcode_case(FM_GLOBAL) {
      char *variable_name = formal_bytecode[++ip];
      MargValue temporary = MARG_STRING(variable_name);
      emit_variable_length_op(OP_GET_GLOBAL);
      emit_temporary(temporary);
    }

    fmcode_case(FM_NIL) { emit_byte(OP_PUT_NIL); }
    fmcode_case(FM_TRUE) { emit_byte(OP_PUT_TRUE); }
    fmcode_case(FM_FALSE) { emit_byte(OP_PUT_FALSE); }

    fmcode_case(FM_SELF) { emit_byte(OP_PUT_SELF); }
    fmcode_case(FM_SUPER) { emit_byte(OP_PUT_SUPER); }

    fmcode_case(FM_INTEGER) {
      char *temporary_str = formal_bytecode[++ip];
      char *end;
      ptrdiff_t integer = strtol(temporary_str, &end, 10);
      if(integer == -1) {
        emit_byte(OP_PUT_MINUS_1);
      } else if(integer == 0) {
        emit_byte(OP_PUT_0);
      } else if(integer == 1) {
        emit_byte(OP_PUT_1);
      } else if(integer == 2) {
        emit_byte(OP_PUT_2);
      } else {
        emit_variable_length_op(OP_PUT_OBJECT);
        emit_temporary(MARG_INTEGER(integer));
      }
    }
    fmcode_case(FM_FLOAT) {
      char *end;
      char *temporary_str = formal_bytecode[++ip];
      MargValue temporary = MARG_FLOAT(strtold(temporary_str, &end));
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(temporary);
    }

    fmcode_case(FM_STRING) {
      char *temporary_str = formal_bytecode[++ip];

      MargValue interned = MARG_STRING_INTERNED(temporary_str);
      emit_variable_length_op(OP_PUT_OBJECT);

      if(IS_NOT_INTERNED(interned)) {
        uint32_t temporary_index;

        interned = MARG_STRING(temporary_str);
        make_temporary(vm, interned, &temporary_index);
        add_temporary(vm, temporary_index);

        table_add(
          &vm->interned_strings, temporary_str, MARG_INTEGER(temporary_index)
        );
      } else {
        uint32_t temporary_index;
        make_temporary(vm, interned, &temporary_index);
        add_temporary(vm, temporary_index);
      }
    }

    fmcode_case(FM_TENSOR) {
      char *end;
      char *number_of_elements = formal_bytecode[++ip];
      MargValue temporary = MARG_INTEGER(strtol(number_of_elements, &end, 10));
      emit_variable_length_op(OP_PUT_TENSOR);
      emit_temporary(temporary);
    }
    fmcode_case(FM_TUPLE) {}
    fmcode_case(FM_HASH) {
      char *end;
      char *number_of_elements = formal_bytecode[++ip];
      MargValue temporary = MARG_INTEGER(strtol(number_of_elements, &end, 10));
      emit_variable_length_op(OP_PUT_HASH);
      emit_temporary(temporary);
    }
    fmcode_case(FM_BITSTRING) {}

    fmcode_case(FM_PROC_START) {
      MargValue new_proc            = MARG_PROC(vm->current->bound_method);
      AS_PROC(new_proc)->bound_proc = vm->current;
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(new_proc);

      vm->current = AS_PROC(new_proc);
    }
    fmcode_case(FM_PROC_END) {
      emit_byte(OP_EXIT_ACTIVATION_RECORD);
      inspect_and_print_proc(vm);
      vm->current = vm->current->bound_proc;
    }

    fmcode_case(FM_METHOD_START) {
      MargValue new_method = MARG_METHOD(
        vm->current->bound_method->bound_object, formal_bytecode[++ip]
      );
      AS_METHOD(new_method)->proc->bound_proc = vm->current;
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(new_method);

      vm->current = AS_METHOD(new_method)->proc;
    }
    fmcode_case(FM_METHOD_END) {
      emit_byte(OP_EXIT_ACTIVATION_RECORD);
      inspect_and_print_method(vm);
      vm->current = vm->current->bound_proc;
    }

    fmcode_case(FM_METHOD_ANY_OBJECT) {}
    fmcode_case(FM_METHOD_PARAMETER) {
      char *parameter_name = formal_bytecode[++ip];
      marg_tensor_add(
        vm->current->bound_method->arguments, MARG_STRING(parameter_name)
      );
    }

    fmcode_case(FM_UNARY) {
      char *unary_name = formal_bytecode[++ip];

      switch_unary_case("call") emit_byte(OP_PROC_CALL);
      default_unary_case {
        emit_byte(OP_PUT_0);
        emit_variable_length_op(OP_SEND);
        emit_temporary(MARG_STRING(unary_name));
      }
    }
    fmcode_case(FM_BINARY) {
      char *binary_name = formal_bytecode[++ip];
      emit_byte(OP_PUT_1);
      emit_variable_length_op(OP_SEND);
      emit_temporary(MARG_STRING(binary_name));
    }
    fmcode_case(FM_KEYWORD) {
      char *keyword_name         = formal_bytecode[++ip];
      char *number_of_parameters = formal_bytecode[++ip];

      switch_keyword_case("puts:") emit_byte(OP_PUTS);
      keyword_case("include:") emit_byte(OP_INCLUDE);
      keyword_case("call:") emit_byte(OP_PROC_CALL_PARAMS);
      keyword_case("primitive_messages:") emit_byte(OP_PRIM_MESSAGES);
      keyword_case("primitive_object_id:") emit_byte(OP_PRIM_OBJECT_ID);
      keyword_case("primitive_to_string:") emit_byte(OP_PRIM_TO_STRING);
      keyword_case("primitive_equals?:with:") emit_byte(OP_PRIM_EQUALS);
      keyword_case("primitive_equals_numeric?:with:")
        emit_byte(OP_PRIM_EQUALS_NUMERIC);
      keyword_case("primitive_dnu:msg:") emit_byte(OP_PRIM_DNU);
      keyword_case("primitive_clone_object:with_name:")
        emit_byte(OP_PRIM_CLONE_OBJECT);
      keyword_case("primitive_bind_method:to:") emit_byte(OP_PRIM_BIND_METHOD);
      keyword_case("primitive_add:with:") emit_byte(OP_PRIM_ADD);
      keyword_case("primitive_sub:with:") emit_byte(OP_PRIM_SUB);
      keyword_case("primitive_mul:with:") emit_byte(OP_PRIM_MUL);
      keyword_case("primitive_div:with:") emit_byte(OP_PRIM_DIV);
      keyword_case("primitive_abs:") emit_byte(OP_PRIM_ABS);
      keyword_case("primitive_less:than:") emit_byte(OP_PRIM_LT);
      keyword_case("primitive_greater:than:") emit_byte(OP_PRIM_GT);
      keyword_case("primitive_less_or_equals:than:") emit_byte(OP_PRIM_LTE);
      keyword_case("primitive_greater_or_equals:than:") emit_byte(OP_PRIM_GTE);
      keyword_case("primitive_incr:") emit_byte(OP_PRIM_INCR);
      keyword_case("primitive_decr:") emit_byte(OP_PRIM_DECR);
      keyword_case("primitive_double:") emit_byte(OP_PRIM_DOUBLE);
      default_keyword_case {
        if(string_equals(number_of_parameters, string_new("1"))) {
          emit_byte(OP_PUT_1);
        } else if(string_equals(number_of_parameters, string_new("2"))) {
          emit_byte(OP_PUT_2);
        } else {
          char *end;
          ptrdiff_t integer = strtol(number_of_parameters, &end, 10);
          emit_variable_length_op(OP_PUT_OBJECT);
          emit_temporary(MARG_INTEGER(integer));
        }

        emit_variable_length_op(OP_SEND);
        emit_temporary(MARG_STRING(keyword_name));
      }
    }
  }

  emit_byte(OP_HALT);
  inspect_and_print_main(vm);

  return vm;
} */

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../opcode/fmcodes.h"
#include "../opcode/MargValue.h"
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
      if(string_equals(temp_int_value, "-1")) {
        /* emit_byte(OP_MINUS_1); */
      } else if(string_equals(temp_int_value, "0")) {
        /* emit_byte(OP_0); */
      } else if(string_equals(temp_int_value, "1")) {
        /* emit_byte(OP_1); */
      } else if(string_equals(temp_int_value, "2")) {
        /* emit_byte(OP_2); */
      } else {
        /* emit_variable_length(OP_OBJECT);
        emit_temporary(temp_int_value); */
      }
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

      /* TODO - Check if interned */
      (void)temp_string_value;
    }
    case_fmcode(FM_LABEL) {
      char *temp_label_value = formal_bytecode[++ip];
      /* emit_variable_length(OP_OBJECT);
      emit_temporary(temp_label_value); */
      (void)temp_label_value;
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
    case_fmcode(FM_HASH) {
      char *number_of_pairs = formal_bytecode[++ip];
      /* emit_variable_length(OP_HASH);
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
      /* TODO - Switch vm pointer to the new method's proc */
      /* MargValue new_method = MARG_METHOD(
        vm->current->bound_method, formal_bytecode[++ip]
      );
      emit_variable_length(OP_OBJECT);
      emit_temporary(new_method);
      vm->current = AS_METHOD(new_method)->proc; */
    }
    case_fmcode(FM_METHOD_END) {
      /* TODO - Switch vm pointer to the proc's parent */
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
        if(string_equals(number_of_parameters, string_new("1"))) {
          /* emit_byte(OP_1); */
        } else if(string_equals(number_of_parameters, string_new("2"))) {
          /* emit_byte(OP_2); */
        } else {
          /* emit_variable_length(OP_OBJECT);
          emit_temporary(MARG_INTEGER(number_of_parameters)); */
        }

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
