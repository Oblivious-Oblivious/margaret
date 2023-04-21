#include "Emitter.h"

#include <string.h> /* strtoll, strtold */

#include "../opcode/Opcodes.h"

#define opcode_case(opstr) else if(string_equals(opcode, (opstr)))

#define EMIT_CONSTANT(constant) do { \
    if(value_vector_size(vm->bytecode->constants) < 256) { \
        chunk_add_with_line(vm->bytecode, OP_CONSTANT, 123); \
        uint8_t constant_index = chunk_add_constant(vm->bytecode, constant); \
        chunk_add_with_line(vm->bytecode, constant_index, 123); \
    } \
    else { \
        chunk_add_with_line(vm->bytecode, OP_LONG_CONSTANT, 123); \
        uint32_t constant_index = chunk_add_constant(vm->bytecode, constant); \
        uint8_t *constant_in_bytes = long_constant_to_bytes(constant_index); \
        chunk_add_with_line(vm->bytecode, constant_in_bytes[0], 123); \
        chunk_add_with_line(vm->bytecode, constant_in_bytes[1], 123); \
        chunk_add_with_line(vm->bytecode, constant_in_bytes[2], 123); \
        chunk_add_with_line(vm->bytecode, constant_in_bytes[3], 123); \
    } \
} while(0)

VM *emitter_emit(vector *formal_bytecode) {
    VM *vm = vm_new();

    size_t bytecode_size = vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        string *opcode = vector_get(formal_bytecode, ip);

        if(string_equals(opcode, FM_VARIABLE)) {}
        opcode_case(FM_INSTANCE) {}

        opcode_case(FM_STORE) {}
        opcode_case(FM_STORE_INSTANCE) {}

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
            EMIT_CONSTANT(constant);
        }
        opcode_case(FM_FLOAT) {
            char *end;
            string *constant_str = vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_NUMBER(strtold(string_get(constant_str), &end));
            EMIT_CONSTANT(constant);
        }

        opcode_case(FM_CHAR) {}
        opcode_case(FM_STRING) {
            string *constant_str = vector_get(formal_bytecode, ++ip);
            char *chars = string_get(constant_str);
            size_t size = string_size(constant_str);
            MargValue constant = MARG_OBJ(obj_string_copy(chars, size));
            EMIT_CONSTANT(constant);
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
