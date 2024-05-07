#include "Emitter.h"

#include "../inspector/Inspector.h"
#include "../opcode/fmcodes.h"
#include "../opcode/MargValue.h"
#include "../opcode/opcodes.h"

#define switch_opcode_case(opstr) if(string_equals(opcode, (opstr)))
#define opcode_case(opstr)        else if(string_equals(opcode, (opstr)))

#define switch_unary_case(unarystr) \
  if(string_equals(unary_name, string_new((unarystr))))
#define unary_case(unarystr) \
  else if(string_equals(unary_name, string_new((unarystr))))
#define default_unary_case else

#define switch_binary_case(binarystr) \
  if(string_equals(binary_name, string_new((binarystr))))
#define binary_case(binarystr) \
  else if(string_equals(binary_name, string_new((binarystr))))
#define default_binary_case else

#define switch_keyword_case(keywordstr) \
  if(string_equals(keyword_name, string_new((keywordstr))))
#define keyword_case(keywordstr) \
  else if(string_equals(keyword_name, string_new((keywordstr))))
#define default_keyword_case else

#define emit_byte(byte) chunk_add(vm->current->bytecode, (byte), 123)

#define emit_bytes2(byte1, byte2) \
  do {                            \
    emit_byte((byte1));           \
    emit_byte((byte2));           \
  } while(0)

#define emit_bytes3(byte1, byte2, byte3) \
  do {                                   \
    emit_byte((byte1));                  \
    emit_byte((byte2));                  \
    emit_byte((byte3));                  \
  } while(0)

#define emit_bytes4(byte1, byte2, byte3, byte4) \
  do {                                          \
    emit_byte((byte1));                         \
    emit_byte((byte2));                         \
    emit_byte((byte3));                         \
    emit_byte((byte4));                         \
  } while(0)

#define emit_variable_length_op(opcode)                            \
  do {                                                             \
    if(chunk_temporaries_size(vm->current->bytecode) < 256)        \
      chunk_add(vm->current->bytecode, (opcode), 123);             \
    else if(chunk_temporaries_size(vm->current->bytecode) < 65536) \
      chunk_add(vm->current->bytecode, (opcode##_WORD), 123);      \
    else                                                           \
      chunk_add(vm->current->bytecode, (opcode##_DWORD), 123);     \
  } while(0)

#define emit_temporary(temporary)                      \
  do {                                                 \
    uint32_t temporary_index;                          \
    make_temporary(vm, (temporary), &temporary_index); \
    add_temporary(vm, temporary_index);                \
  } while(0)

#define make_temporary(vm, temporary, index) \
  chunk_temporaries_add((vm)->current->bytecode, (temporary), (index));

#define add_temporary(vm, temporary_index) \
  __add_temporary_function(vm, temporary_index, 256 + 1, 65536 + 1);
#define add_premade_temporary(vm, temporary_index) \
  __add_temporary_function(vm, temporary_index, 256, 65536);

static void __add_temporary_function(
  VM *vm, uint32_t temporary_index, uint16_t byte_bound, uint32_t word_bound
) {
  if(chunk_temporaries_size(vm->current->bytecode) < byte_bound) {
    emit_byte((uint8_t)temporary_index);
  } else if(chunk_temporaries_size(vm->current->bytecode) < word_bound) {
    uint8_t *temporary_index_in_bytes = word_to_bytes(temporary_index);
    emit_bytes2(temporary_index_in_bytes[0], temporary_index_in_bytes[1]);
  } else {
    uint8_t *temporary_index_in_bytes = dword_to_bytes(temporary_index);
    emit_bytes4(
      temporary_index_in_bytes[0],
      temporary_index_in_bytes[1],
      temporary_index_in_bytes[2],
      temporary_index_in_bytes[3]
    );
  }
}

VM *emitter_emit(VM *vm, vector *formal_bytecode) {
  MargObject *marg_object =
    AS_OBJECT(table_get(&vm->global_variables, MARG_STRING("$Margaret")));
  MargMethod *main_method =
    AS_METHOD(table_get(&marg_object->messages, MARG_STRING("")));
  vm->current->bytecode = chunk_new();
  vm->current           = main_method->proc;

  size_t bytecode_size = vector_size(formal_bytecode);
  for(size_t ip = 0; ip < bytecode_size; ip++) {
    string *opcode = vector_get(formal_bytecode, ip);

    switch_opcode_case(FM_POP) { emit_byte(OP_POP); }

    opcode_case(FM_LOCAL) {
      string *variable_name = vector_get(formal_bytecode, ++ip);
      MargValue temporary   = MARG_STRING(variable_name->str);
      emit_variable_length_op(OP_GET_LOCAL);
      emit_temporary(temporary);
    }
    opcode_case(FM_INSTANCE) {
      string *variable_name = vector_get(formal_bytecode, ++ip);
      MargValue temporary   = MARG_STRING(variable_name->str);
      emit_variable_length_op(OP_GET_INSTANCE);
      emit_temporary(temporary);
    }
    opcode_case(FM_GLOBAL) {
      string *variable_name = vector_get(formal_bytecode, ++ip);
      MargValue temporary   = MARG_STRING(variable_name->str);
      emit_variable_length_op(OP_GET_GLOBAL);
      emit_temporary(temporary);
    }

    opcode_case(FM_STORE_LOCAL) {
      string *variable_name = vector_get(formal_bytecode, ++ip);
      emit_variable_length_op(OP_SET_LOCAL);
      emit_temporary(MARG_STRING(variable_name->str));
    }
    opcode_case(FM_STORE_INSTANCE) {
      string *variable_name = vector_get(formal_bytecode, ++ip);
      emit_variable_length_op(OP_SET_INSTANCE);
      emit_temporary(MARG_STRING(variable_name->str));
    }
    opcode_case(FM_STORE_GLOBAL) {
      string *variable_name = vector_get(formal_bytecode, ++ip);
      emit_variable_length_op(OP_SET_GLOBAL);
      emit_temporary(MARG_STRING(variable_name->str));
    }

    opcode_case(FM_NIL) { emit_byte(OP_PUT_NIL); }
    opcode_case(FM_TRUE) { emit_byte(OP_PUT_TRUE); }
    opcode_case(FM_FALSE) { emit_byte(OP_PUT_FALSE); }

    opcode_case(FM_SELF) { emit_byte(OP_PUT_SELF); }
    opcode_case(FM_SUPER) { emit_byte(OP_PUT_SUPER); }

    // TODO Distinguish normal number from big numbers
    opcode_case(FM_INTEGER) {
      string *temporary_str = vector_get(formal_bytecode, ++ip);
      char *end;
      long long integer = strtoll(string_get(temporary_str), &end, 10);
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
    opcode_case(FM_FLOAT) {
      char *end;
      string *temporary_str = vector_get(formal_bytecode, ++ip);
      MargValue temporary =
        MARG_FLOAT(strtold(string_get(temporary_str), &end));
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(temporary);
    }

    opcode_case(FM_STRING) {
      string *temporary_str = vector_get(formal_bytecode, ++ip);
      char *chars           = string_get(temporary_str);
      size_t size           = string_size(temporary_str);

      MargValue interned = MARG_STRING_INTERNED(chars, size);
      emit_variable_length_op(OP_PUT_OBJECT);

      if(IS_NOT_INTERNED(interned)) {
        interned = MARG_STRING(chars);

        uint32_t temporary_index;
        make_temporary(vm, interned, &temporary_index);
        add_temporary(vm, temporary_index);

        table_set(
          &vm->interned_strings, interned, MARG_INTEGER(temporary_index)
        );
      } else {
        uint32_t temporary_index;
        make_temporary(vm, interned, &temporary_index);
        add_temporary(vm, temporary_index);
      }
    }

    opcode_case(FM_TENSOR) {
      char *end;
      string *number_of_elements = vector_get(formal_bytecode, ++ip);
      MargValue temporary =
        MARG_INTEGER(strtoll(string_get(number_of_elements), &end, 10));
      emit_variable_length_op(OP_PUT_TENSOR);
      emit_temporary(temporary);
    }
    opcode_case(FM_TUPLE) {}
    opcode_case(FM_HASH) {
      char *end;
      string *number_of_elements = vector_get(formal_bytecode, ++ip);
      MargValue temporary =
        MARG_INTEGER(strtoll(string_get(number_of_elements), &end, 10));
      emit_variable_length_op(OP_PUT_HASH);
      emit_temporary(temporary);
    }
    opcode_case(FM_BITSTRING) {}

    opcode_case(FM_START_PROC) {
      MargValue new_proc            = MARG_PROC(vm->current->bound_method);
      AS_PROC(new_proc)->bound_proc = vm->current;
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(new_proc);

      vm->current = AS_PROC(new_proc);
    }
    opcode_case(FM_END_PROC) {
      emit_byte(OP_EXIT_ACTIVATION_RECORD);
      inspect_and_print_proc(vm);
      vm->current = vm->current->bound_proc;
    }

    opcode_case(FM_START_C_FUNCTION) {}
    opcode_case(FM_END_C_FUNCTION) {}

    opcode_case(FM_START_UNARY_METHOD) {
      MargValue new_method = MARG_METHOD(
        vm->current->bound_method->bound_object,
        string_get(vector_get(formal_bytecode, ++ip))
      );
      AS_METHOD(new_method)->proc->bound_proc = vm->current;
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(new_method);

      vm->current = AS_METHOD(new_method)->proc;
    }
    opcode_case(FM_END_UNARY_METHOD) {
      emit_byte(OP_EXIT_ACTIVATION_RECORD);
      inspect_and_print_method(vm);
      vm->current = vm->current->bound_proc;
    }
    opcode_case(FM_START_BINARY_METHOD) {
      MargValue new_method = MARG_METHOD(
        vm->current->bound_method->bound_object,
        string_get(vector_get(formal_bytecode, ++ip))
      );
      AS_METHOD(new_method)->proc->bound_proc = vm->current;
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(new_method);

      vm->current = AS_METHOD(new_method)->proc;
    }
    opcode_case(FM_END_BINARY_METHOD) {
      emit_byte(OP_EXIT_ACTIVATION_RECORD);
      inspect_and_print_method(vm);
      vm->current = vm->current->bound_proc;
    }
    opcode_case(FM_START_KEYWORD_METHOD) {
      MargValue new_method = MARG_METHOD(
        vm->current->bound_method->bound_object,
        string_get(vector_get(formal_bytecode, ++ip))
      );
      AS_METHOD(new_method)->proc->bound_proc = vm->current;
      emit_variable_length_op(OP_PUT_OBJECT);
      emit_temporary(new_method);

      vm->current = AS_METHOD(new_method)->proc;
    }
    opcode_case(FM_END_KEYWORD_METHOD) {
      emit_byte(OP_EXIT_ACTIVATION_RECORD);
      inspect_and_print_method(vm);
      vm->current = vm->current->bound_proc;
    }

    opcode_case(FM_ANY_OBJECT) {}
    opcode_case(FM_METHOD_PARAMETER) {
      char *parameter_name = string_get(vector_get(formal_bytecode, ++ip));
      marg_tensor_add(
        vm->current->bound_method->parameter_names, MARG_STRING(parameter_name)
      );
    }

    opcode_case(FM_UNARY) {
      string *unary_name = vector_get(formal_bytecode, ++ip);

      switch_unary_case("call") emit_byte(OP_PROC_CALL);
      default_unary_case {
        emit_byte(OP_PUT_0);
        emit_variable_length_op(OP_SEND);
        emit_temporary(MARG_STRING(string_get(unary_name)));
      }
    }
    opcode_case(FM_BINARY) {
      string *binary_name = vector_get(formal_bytecode, ++ip);
      emit_byte(OP_PUT_1);
      emit_variable_length_op(OP_SEND);
      emit_temporary(MARG_STRING(string_get(binary_name)));
    }
    opcode_case(FM_KEYWORD) {
      string *keyword_name         = vector_get(formal_bytecode, ++ip);
      string *number_of_parameters = vector_get(formal_bytecode, ++ip);

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
          long long integer =
            strtoll(string_get(number_of_parameters), &end, 10);
          emit_variable_length_op(OP_PUT_OBJECT);
          emit_temporary(MARG_INTEGER(integer));
        }

        emit_variable_length_op(OP_SEND);
        emit_temporary(MARG_STRING(string_get(keyword_name)));
      }
    }
  }

  emit_byte(OP_HALT);
  inspect_and_print_main(vm);

  return vm;
}
