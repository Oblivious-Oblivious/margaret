#include "Emitter.h"

#include <string.h> /* strtoll, strtold */

#include "../opcode/Opcodes.h"

#define opcode_case(opstr) else if(string_equals(opcode, (opstr)))

static uint32_t make_constant(VM *vm, MargValue constant) {
    if(value_vector_size(vm->bytecode->constants) < 256)
        return chunk_add_constant(vm->bytecode, constant);
    else
        return chunk_add_long_constant(vm->bytecode, constant);
}

static void add_constant(VM *vm, uint32_t constant_index) {
    if(constant_index < 256) {
        chunk_add_with_line(vm->bytecode, (uint8_t)constant_index, 123);
    }
    else {
        uint8_t *constant_index_in_bytes = long_constant_to_bytes(constant_index);
        chunk_add_with_line(vm->bytecode, constant_index_in_bytes[0], 123);
        chunk_add_with_line(vm->bytecode, constant_index_in_bytes[1], 123);
        chunk_add_with_line(vm->bytecode, constant_index_in_bytes[2], 123);
        chunk_add_with_line(vm->bytecode, constant_index_in_bytes[3], 123);
    }
}

#define EMIT_CONSTANT() add_constant(vm, make_constant(vm, constant));

#define EMIT_POSSIBLE_LONG_OP(opcode) do { \
    if(value_vector_size(vm->bytecode->constants) < 256) \
        chunk_add_with_line(vm->bytecode, (opcode), 123); \
    else \
        chunk_add_with_line(vm->bytecode, (opcode##_LONG), 123); \
} while(0)

VM *emitter_emit(vector *formal_bytecode) {
    VM *vm = vm_new();

    size_t bytecode_size = vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        string *opcode = vector_get(formal_bytecode, ip);

        if(string_equals(opcode, FM_LOCAL)) {}
        opcode_case(FM_INSTANCE) {}
        opcode_case(FM_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_OBJECT(marg_string_copy(variable_name->str, variable_name->size));
            EMIT_POSSIBLE_LONG_OP(OP_GLOBAL);
            EMIT_CONSTANT();
        }

        opcode_case(FM_STORE_LOCAL) {}
        opcode_case(FM_STORE_INSTANCE) {}
        opcode_case(FM_STORE_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);

            EMIT_POSSIBLE_LONG_OP(OP_STORE_GLOBAL);

            uint32_t constant_index;
            MargString *str = marg_string_copy(variable_name->str, variable_name->size);
            MargValue index;
            if(marg_hash_get(&vm->string_constants, str, &index)) {
                constant_index = (uint32_t)AS_NUMBER(index);
            }
            else {
                constant_index = make_constant(vm, MARG_OBJECT(str));
                marg_hash_set(&vm->string_constants, str, MARG_NUMBER((long double)constant_index));
            }

            if(value_vector_size(vm->bytecode->constants) < 256) {
                chunk_add_with_line(vm->bytecode, (uint8_t)constant_index, 123);
            }
            else {
                uint8_t *constant_index_in_bytes = long_constant_to_bytes(constant_index);
                chunk_add_with_line(vm->bytecode, constant_index_in_bytes[0], 123);
                chunk_add_with_line(vm->bytecode, constant_index_in_bytes[1], 123);
                chunk_add_with_line(vm->bytecode, constant_index_in_bytes[2], 123);
                chunk_add_with_line(vm->bytecode, constant_index_in_bytes[3], 123);
            }
        }

        opcode_case(FM_NIL) {
            chunk_add_with_line(vm->bytecode, OP_NIL, 123);
        }
        opcode_case(FM_TRUE) {
            chunk_add_with_line(vm->bytecode, OP_TRUE, 123);
        }
        opcode_case(FM_FALSE) {
            chunk_add_with_line(vm->bytecode, OP_FALSE, 123);
        }

        opcode_case(FM_SELF) {}
        opcode_case(FM_SUPER) {}

        // TODO Distinguish normal number from big numbers
        opcode_case(FM_INTEGER) {
            char *end;
            string *constant_str = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_NUMBER(strtoll(string_get(constant_str), &end, 10));
            EMIT_POSSIBLE_LONG_OP(OP_CONSTANT);
            EMIT_CONSTANT();
        }
        opcode_case(FM_FLOAT) {
            char *end;
            string *constant_str = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_NUMBER(strtold(string_get(constant_str), &end));
            EMIT_POSSIBLE_LONG_OP(OP_CONSTANT);
            EMIT_CONSTANT();
        }

        opcode_case(FM_STRING) {
            string *constant_str = vector_get(formal_bytecode, ++ip);
            char *chars = string_get(constant_str);
            size_t size = string_size(constant_str);

            uint64_t hash = marg_string_hash(chars, size);
            MargString *interned = marg_hash_find_string(&vm->interned_strings, chars, size, hash);
            if(interned == NULL) {
                interned = marg_string_copy(chars, size);
                marg_hash_set(&vm->interned_strings, interned, MARG_NIL);
            }

            MargValue constant = MARG_OBJECT(interned);
            EMIT_POSSIBLE_LONG_OP(OP_CONSTANT);
            EMIT_CONSTANT();
        }

        opcode_case(FM_TENSOR) {}
        opcode_case(FM_TUPLE) {}
        opcode_case(FM_HASH) {}
        opcode_case(FM_BITSTRING) {}

        opcode_case(FM_ANY_OBJECT) {}
        opcode_case(FM_METHOD_PARAMETER) {}

        opcode_case(FM_START_PROC) {}
        opcode_case(FM_END_PROC) {}
        opcode_case(FM_START_C_FUNCTION) {}
        opcode_case(FM_END_C_FUNCTION) {}

        opcode_case(FM_UNARY) {}
        opcode_case(FM_BINARY) {}
        opcode_case(FM_KEYWORD) {}
    }

    chunk_add_with_line(vm->bytecode, OP_RETURN, 123);
    return vm;
}
