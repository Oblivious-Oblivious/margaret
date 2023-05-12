#include "Emitter.h"

#include <string.h> /* strtoll, strtold */

#include "../inspector/Inspector.h"

#include "../base/chunk.h"
#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"
#include "../opcode/MargInteger.h"
#include "../opcode/MargFloat.h"
#include "../opcode/MargString.h"
#include "../opcode/MargProc.h"
#include "../vm/byte_conversions.h"

#define switch_opcode_case(opstr) if(string_equals(opcode, (opstr)))
#define opcode_case(opstr) else if(string_equals(opcode, (opstr)))

#define emit_byte(byte) chunk_add(vm->current->bytecode, (byte), 123)

#define emit_bytes2(byte1, byte2) do { \
    emit_byte((byte1)); \
    emit_byte((byte2)); \
} while(0)

#define emit_bytes3(byte1, byte2, byte3) do { \
    emit_byte((byte1)); \
    emit_byte((byte2)); \
    emit_byte((byte3)); \
} while(0)

#define emit_bytes4(byte1, byte2, byte3, byte4) do { \
    emit_byte((byte1)); \
    emit_byte((byte2)); \
    emit_byte((byte3)); \
    emit_byte((byte4)); \
} while(0)

#define emit_possible_long_op(opcode) do { \
    if(chunk_temporaries_size(vm->current->bytecode) < 256) \
        chunk_add(vm->current->bytecode, (opcode), 123); \
    else \
        chunk_add(vm->current->bytecode, (opcode##_LONG), 123); \
} while(0)

#define emit_temporary(temporary) do { \
    uint32_t temporary_index; \
    make_temporary(vm, (temporary), &temporary_index); \
    add_temporary(vm, temporary_index); \
} while(0)

#define make_temporary(vm, temporary, index) \
    chunk_temporaries_add((vm)->current->bytecode, (temporary), (index));

#define add_temporary(vm, temporary_index) \
    __add_temporary_function(vm, temporary_index, 256+1);
#define add_premade_temporary(vm, temporary_index) \
    __add_temporary_function(vm, temporary_index, 256);

static void __add_temporary_function(VM *vm, uint32_t temporary_index, uint16_t upper_bound) {
    if(chunk_temporaries_size(vm->current->bytecode) < upper_bound) {
        emit_byte((uint8_t)temporary_index);
    }
    else {
        uint8_t *temporary_index_in_bytes = dword_to_bytes(temporary_index);
        emit_bytes4(
            temporary_index_in_bytes[0],
            temporary_index_in_bytes[1],
            temporary_index_in_bytes[2],
            temporary_index_in_bytes[3]
        );
    }
}

VM *emitter_emit(vector *formal_bytecode) {
    VM *vm = vm_new();
    MargObject *marg_object = AS_OBJECT(table_get(&vm->global_variables, MARG_STRING("$Margaret")));
    MargMethod *main_method = AS_METHOD(table_get(&marg_object->messages, MARG_STRING("main:")));
    vm->current = main_method->proc;

    size_t bytecode_size = vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        string *opcode = vector_get(formal_bytecode, ip);

        switch_opcode_case(FM_POP) {
            emit_byte(OP_POP);
        }

        opcode_case(FM_LOCAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_STRING(variable_name->str);
            emit_possible_long_op(OP_GET_LOCAL);
            emit_temporary(temporary);
        }
        opcode_case(FM_INSTANCE) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_STRING(variable_name->str);
            emit_possible_long_op(OP_GET_INSTANCE);
            emit_temporary(temporary);
        }
        opcode_case(FM_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_STRING(variable_name->str);
            emit_possible_long_op(OP_GET_GLOBAL);
            emit_temporary(temporary);
        }

        opcode_case(FM_STORE_LOCAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            emit_possible_long_op(OP_SET_LOCAL);
            emit_temporary(MARG_STRING(variable_name->str));
        }
        opcode_case(FM_STORE_INSTANCE) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            emit_possible_long_op(OP_SET_INSTANCE);
            emit_temporary(MARG_STRING(variable_name->str));
        }
        opcode_case(FM_STORE_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            emit_possible_long_op(OP_SET_GLOBAL);
            emit_temporary(MARG_STRING(variable_name->str));
        }

        opcode_case(FM_NIL) {
            emit_byte(OP_PUT_NIL);
        }
        opcode_case(FM_TRUE) {
            emit_byte(OP_PUT_TRUE);
        }
        opcode_case(FM_FALSE) {
            emit_byte(OP_PUT_FALSE);
        }

        opcode_case(FM_SELF) {}
        opcode_case(FM_SUPER) {}

        // TODO Distinguish normal number from big numbers
        opcode_case(FM_INTEGER) {
            string *temporary_str = vector_get(formal_bytecode, ++ip);
            char *end; long long integer = strtoll(string_get(temporary_str), &end, 10);
            if(integer == -1)
                emit_byte(OP_PUT_MINUS_1);
            else if(integer == 0)
                emit_byte(OP_PUT_0);
            else if(integer == 1)
                emit_byte(OP_PUT_1);
            else if(integer == 2)
                emit_byte(OP_PUT_2);
            else {
                emit_possible_long_op(OP_PUT_OBJECT);
                emit_temporary(MARG_INTEGER(integer));
            }
        }
        opcode_case(FM_FLOAT) {
            char *end;
            string *temporary_str = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_FLOAT(strtold(string_get(temporary_str), &end));
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(temporary);
        }

        opcode_case(FM_STRING) {
            string *temporary_str = vector_get(formal_bytecode, ++ip);
            char *chars = string_get(temporary_str);
            size_t size = string_size(temporary_str);

            MargValue interned = MARG_STRING_INTERNED(chars, size);
            emit_possible_long_op(OP_PUT_OBJECT);

            if(IS_NOT_INTERNED(interned)) {
                interned = MARG_STRING(chars);

                uint32_t temporary_index;
                make_temporary(vm, interned, &temporary_index);
                add_temporary(vm, temporary_index);

                table_set(&vm->interned_strings, interned, MARG_INTEGER(temporary_index));
            }
            else {
                uint32_t temporary_index;
                make_temporary(vm, interned, &temporary_index);
                add_temporary(vm, temporary_index);
            }
        }

        opcode_case(FM_TENSOR) {
            char *end;
            string *number_of_elements = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_INTEGER(strtoll(string_get(number_of_elements), &end, 10));
            emit_possible_long_op(OP_PUT_TENSOR);
            emit_temporary(temporary);
        }
        opcode_case(FM_TUPLE) {}
        opcode_case(FM_HASH) {
            char *end;
            string *number_of_elements = vector_get(formal_bytecode, ++ip);
            MargValue temporary = MARG_INTEGER(strtoll(string_get(number_of_elements), &end, 10));
            emit_possible_long_op(OP_PUT_HASH);
            emit_temporary(temporary);
        }
        opcode_case(FM_BITSTRING) {}

        opcode_case(FM_START_PROC) {
            MargValue new_proc = MARG_PROC(vm->current->bound_method);
            AS_PROC(new_proc)->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_proc);

            vm->current = AS_PROC(new_proc);
        }
        opcode_case(FM_END_PROC) {
            emit_byte(OP_EXIT_PROC);
            inspect_and_print_proc(vm);
            vm->current = vm->current->bound_proc;
        }

        opcode_case(FM_START_C_FUNCTION) {}
        opcode_case(FM_END_C_FUNCTION) {}

        opcode_case(FM_START_UNARY_METHOD) {
            MargValue new_method = MARG_METHOD(vm->current->bound_method->bound_object);
            AS_METHOD(new_method)->proc->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_method);
            emit_byte(OP_SEND);

            vm->current = AS_METHOD(new_method)->proc;
        }
        opcode_case(FM_END_UNARY_METHOD) {
            emit_byte(OP_EXIT_METHOD);
            inspect_and_print_method(vm);
            vm->current = vm->current->bound_proc;
        }
        opcode_case(FM_START_BINARY_METHOD) {
            MargValue new_method = MARG_METHOD(vm->current->bound_method->bound_object);
            AS_METHOD(new_method)->proc->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_method);
            emit_byte(OP_SEND);

            vm->current = AS_METHOD(new_method)->proc;
        }
        opcode_case(FM_END_BINARY_METHOD) {
            // emit_byte(OP_POP);
            emit_byte(OP_EXIT_METHOD);
            inspect_and_print_method(vm);
            vm->current = vm->current->bound_proc;
        }
        opcode_case(FM_START_KEYWORD_METHOD) {
            MargValue new_method = MARG_METHOD(vm->current->bound_method->bound_object);
            AS_METHOD(new_method)->proc->bound_proc = vm->current;
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_temporary(new_method);
            emit_byte(OP_SEND);

            vm->current = AS_METHOD(new_method)->proc;
        }
        opcode_case(FM_END_KEYWORD_METHOD) {
            // emit_byte(OP_POP);
            // emit_byte(OP_POP);
            emit_byte(OP_EXIT_METHOD);
            inspect_and_print_method(vm);
            vm->current = vm->current->bound_proc;
        }

        opcode_case(FM_UNARY) {
            emit_byte(TEST_OP_PRINT);
        }
        opcode_case(FM_BINARY) {}
        opcode_case(FM_KEYWORD) {}
    }

    emit_byte(OP_HALT);
    inspect_and_print_main(vm);

    return vm;
}
