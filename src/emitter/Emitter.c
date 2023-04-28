#include "Emitter.h"

// TODO https://stackoverflow.com/questions/17002969/how-to-convert-string-to-int64-t
#include <string.h> /* strtoll, strtold */

#include "../base/Constants.h"
#include "../base/Chunk.h"
#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"

#define opcode_case(opstr) else if(string_equals(opcode, (opstr)))

#define emit_byte(byte) chunk_add(vm->bytecode, (byte), 123)

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
    if(constants_size(vm->bytecode->constants) < 256) \
        chunk_add(vm->bytecode, (opcode), 123); \
    else \
        chunk_add(vm->bytecode, (opcode##_LONG), 123); \
} while(0)

#define emit_constant(constant) do { \
    uint32_t constant_index = make_constant(vm, (constant)); \
    add_constant(vm, constant_index); \
} while(0)

static uint32_t make_constant(VM *vm, MargValue constant) {
    return chunk_constant_add(vm->bytecode, constant);
}

static void add_constant(VM *vm, uint32_t constant_index) {
    if(constants_size(vm->bytecode->constants) < 256+1) {
        emit_byte((uint8_t)constant_index);
    }
    else {
        uint8_t *constant_index_in_bytes = dword_to_bytes(constant_index);
        emit_bytes4(
            constant_index_in_bytes[0],
            constant_index_in_bytes[1],
            constant_index_in_bytes[2],
            constant_index_in_bytes[3]
        );
    }
}

static void add_premade_constant(VM *vm, uint32_t constant_index) {
    if(constants_size(vm->bytecode->constants) < 256) {
        emit_byte((uint8_t)constant_index);
    }
    else {
        uint8_t *constant_index_in_bytes = dword_to_bytes(constant_index);
        emit_bytes4(
            constant_index_in_bytes[0],
            constant_index_in_bytes[1],
            constant_index_in_bytes[2],
            constant_index_in_bytes[3]
        );
    }
}

VM *emitter_emit(vector *formal_bytecode) {
    VM *vm = vm_new();

    size_t bytecode_size = vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        string *opcode = vector_get(formal_bytecode, ip);

        if(string_equals(opcode, FM_LOCAL)) {}
        opcode_case(FM_INSTANCE) {}
        opcode_case(FM_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_STRING(variable_name->str, variable_name->size);
            emit_possible_long_op(OP_GET_GLOBAL);
            emit_constant(constant);
        }

        opcode_case(FM_STORE_LOCAL) {}
        opcode_case(FM_STORE_INSTANCE) {}
        opcode_case(FM_STORE_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);

            emit_possible_long_op(OP_SET_GLOBAL);

            uint32_t constant_index;
            MargValue str = MARG_STRING(variable_name->str, variable_name->size);
            MargValue index;
            if(marg_hash_get(&vm->interned_strings, AS_STRING(str), &index)) {
                constant_index = (uint32_t)AS_INTEGER(index)->value;
                add_premade_constant(vm, constant_index);
            }
            else {
                constant_index = make_constant(vm, MARG_OBJECT(str));
                marg_hash_set(&vm->interned_strings, AS_STRING(str), MARG_INTEGER(constant_index));
                add_constant(vm, constant_index);
            }
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
            char *end;
            string *constant_str = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_INTEGER(strtoll(string_get(constant_str), &end, 10));
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_constant(constant);
        }
        opcode_case(FM_FLOAT) {
            char *end;
            string *constant_str = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_FLOAT(strtold(string_get(constant_str), &end));
            emit_possible_long_op(OP_PUT_OBJECT);
            emit_constant(constant);
        }

        opcode_case(FM_STRING) {
            string *constant_str = vector_get(formal_bytecode, ++ip);
            char *chars = string_get(constant_str);
            size_t size = string_size(constant_str);

            uint64_t hash = marg_string_hash(chars, size);
            MargValue interned = MARG_STRING_INTERNED(vm, chars, size, hash);
            emit_possible_long_op(OP_PUT_OBJECT);

            if(AS_STRING(interned) == NULL) {
                interned = MARG_STRING(chars, size);

                uint32_t constant_index = make_constant(vm, interned);
                add_constant(vm, constant_index);

                marg_hash_set(&vm->interned_strings, AS_STRING(interned), MARG_INTEGER(constant_index));
            }
            else {
                uint32_t constant_index = make_constant(vm, interned);
                add_constant(vm, constant_index);
            }
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

        opcode_case(FM_UNARY) {
            emit_byte(TEST_OP_PRINT);
        }
        opcode_case(FM_BINARY) {}
        opcode_case(FM_KEYWORD) {}
    }

    emit_byte(OP_RETURN);
    return vm;
}
