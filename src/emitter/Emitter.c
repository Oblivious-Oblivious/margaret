#include "Emitter.h"

// TODO https://stackoverflow.com/questions/17002969/how-to-convert-string-to-int64-t
#include <string.h> /* strtoll, strtold */

#include "../base/chunk.h"
#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"
#include "../vm/byte_conversions.h"

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
    if(chunk_temporaries_size(vm->bytecode) < 256) \
        chunk_add(vm->bytecode, (opcode), 123); \
    else \
        chunk_add(vm->bytecode, (opcode##_LONG), 123); \
} while(0)

#define emit_temporary(temporary) do { \
    uint32_t temporary_index; \
    make_temporary(vm, (temporary), &temporary_index); \
    add_temporary(vm, temporary_index); \
} while(0)

static void make_temporary(VM *vm, MargValue temporary, uint32_t *index) {
    chunk_temporaries_add(vm->bytecode, temporary, index);
}

static void __add_temporary_function(VM *vm, uint32_t temporary_index, uint16_t upper_bound) {
    if(chunk_temporaries_size(vm->bytecode) < upper_bound) {
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

static void add_temporary(VM *vm, uint32_t temporary_index) {
    __add_temporary_function(vm, temporary_index, 256+1);
}
static void add_premade_temporary(VM *vm, uint32_t temporary_index) {
    __add_temporary_function(vm, temporary_index, 256);
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
            MargValue temporary = MARG_STRING(variable_name->str, variable_name->size);
            emit_possible_long_op(OP_GET_GLOBAL);
            emit_temporary(temporary);
        }

        opcode_case(FM_STORE_LOCAL) {}
        opcode_case(FM_STORE_INSTANCE) {}
        opcode_case(FM_STORE_GLOBAL) {
            string *variable_name = vector_get(formal_bytecode, ++ip);

            emit_possible_long_op(OP_SET_GLOBAL);

            MargValue temporary = MARG_STRING(variable_name->str, variable_name->size);
            MargValue index;
            if(table_get(&vm->interned_strings, AS_STRING(temporary), &index)) {
                add_premade_temporary(vm, (uint32_t)AS_INTEGER(index)->value);
            }
            else {
                uint32_t temporary_index;
                make_temporary(vm, temporary, &temporary_index);
                table_set(&vm->interned_strings, AS_STRING(temporary), MARG_INTEGER(temporary_index));
                add_temporary(vm, temporary_index);
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

            uint64_t hash = marg_string_hash(chars, size);
            MargValue interned = MARG_STRING_INTERNED(vm, chars, size, hash);
            emit_possible_long_op(OP_PUT_OBJECT);

            if(AS_STRING(interned) == NULL) {
                interned = MARG_STRING(chars, size);

                uint32_t temporary_index;
                make_temporary(vm, interned, &temporary_index);
                add_temporary(vm, temporary_index);

                table_set(&vm->interned_strings, AS_STRING(interned), MARG_INTEGER(temporary_index));
            }
            else {
                uint32_t temporary_index;
                make_temporary(vm, interned, &temporary_index);
                add_temporary(vm, temporary_index);
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
