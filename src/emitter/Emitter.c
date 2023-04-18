#include "Emitter.h"

#include "../opcode/Opcodes.h"

#define opcode_case(opstr) else if(marg_string_equals(opcode, (opstr)))

VM *emitter_emit(marg_vector *formal_bytecode) {
    VM *vm = vm_new();

    size_t bytecode_size = marg_vector_size(formal_bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        marg_string *opcode = marg_vector_get(formal_bytecode, ip);

        if(marg_string_equals(opcode, FM_NIL)) {}
        opcode_case(FM_TRUE) {}
        opcode_case(FM_FALSE) {}

        opcode_case(FM_SELF) {}
        opcode_case(FM_SUPER) {}

        opcode_case(FM_0) {
            if(value_vector_size(vm->bytecode->constants) < 256) {
                chunk_add_with_line(vm->bytecode, OP_CONSTANT, 123);
                uint8_t constant = chunk_add_constant(vm->bytecode, 0);
                chunk_add_with_line(vm->bytecode, constant, 123);
            }
            else {
                chunk_add_with_line(vm->bytecode, OP_LONG_CONSTANT, 123);
                uint32_t long_constant = chunk_add_long_constant(vm->bytecode, 0);
                uint8_t *constant_in_bytes = long_constant_to_bytes(long_constant);
                chunk_add_with_line(vm->bytecode, constant_in_bytes[0], 123);
                chunk_add_with_line(vm->bytecode, constant_in_bytes[1], 123);
                chunk_add_with_line(vm->bytecode, constant_in_bytes[2], 123);
                chunk_add_with_line(vm->bytecode, constant_in_bytes[3], 123);
            }
        }
        opcode_case(FM_1) {}
        opcode_case(FM_MINUS_1) {}
        opcode_case(FM_2) {}

        opcode_case(FM_VARIABLE) {}
        opcode_case(FM_INSTANCE) {}

        opcode_case(FM_INTEGER) {}
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

        opcode_case(FM_STORE) {}
        opcode_case(FM_STORE_INSTANCE) {}

        opcode_case(FM_METHOD_UNARY) {}
        opcode_case(FM_METHOD_BINARY) {}
        opcode_case(FM_METHOD_KEYWORD) {}

        opcode_case(FM_UNARY) {}
        opcode_case(FM_BINARY) {}
        opcode_case(FM_KEYWORD) {}
    }

    chunk_add_with_line(vm->bytecode, OP_RETURN, 123);
    return vm;
}
