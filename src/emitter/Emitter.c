#include "Emitter.h"

#include "../opcode/Opcodes.h"

#define opcode_case(opstr) else if(marg_string_equals(opcode, (opstr)))

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

VM *emitter_emit(marg_vector *formal_bytecode) {
    VM *vm = vm_new();

    size_t bytecode_size = marg_vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        marg_string *opcode = marg_vector_get(formal_bytecode, ip);

        if(marg_string_equals(opcode, FM_VARIABLE)) {}
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

        opcode_case(FM_INTEGER) {
            marg_string *constant_str = marg_vector_get(formal_bytecode, ++ip);
            MargValue constant = MARG_NUMBER((long long)atoi(marg_string_get(constant_str)));
            EMIT_CONSTANT(constant);
        }
        opcode_case(FM_FLOAT) {}
        opcode_case(FM_CHAR) {}
        opcode_case(FM_STRING) {}
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
