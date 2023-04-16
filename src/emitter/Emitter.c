#include "Emitter.h"

#include "../opcode/Opcodes.h"

#define opcode_case(opstr) if(marg_string_equals(opcode, (opstr)))

Emitter *emitter_new(marg_vector *bytecode) {
    Emitter *self = (Emitter*)collected_malloc(sizeof(Emitter));

    self->stack.top = -1;
    self->bytecode = bytecode;

    return self;
}

Chunk *emitter_emit(Emitter *self) {
    size_t bytecode_size = marg_vector_size(self->bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        marg_string *opcode = marg_vector_get(self->bytecode, ip);

        opcode_case(OP_NIL) {}
        opcode_case(OP_TRUE) {}
        opcode_case(OP_FALSE) {}

        opcode_case(OP_SELF) {}
        opcode_case(OP_SUPER) {}

        opcode_case(OP_0) {}
        opcode_case(OP_1) {}
        opcode_case(OP_MINUS_1) {}
        opcode_case(OP_2) {}

        opcode_case(OP_VARIABLE) {}
        opcode_case(OP_INSTANCE) {}

        opcode_case(OP_INTEGER) {}
        opcode_case(OP_FLOAT) {}
        opcode_case(OP_CHAR) {}
        opcode_case(OP_STRING) {}
        opcode_case(OP_TENSOR) {}
        opcode_case(OP_TUPLE) {}
        opcode_case(OP_HASH) {}
        opcode_case(OP_BITSTRING) {}

        opcode_case(OP_ANY_OBJECT) {}
        opcode_case(OP_METHOD_PARAMETER) {}

        opcode_case(OP_START_PROC) {}
        opcode_case(OP_END_PROC) {}
        opcode_case(OP_START_C_FUNCTION) {}
        opcode_case(OP_END_C_FUNCTION) {}

        opcode_case(OP_STORE) {}
        opcode_case(OP_STORE_INSTANCE) {}

        opcode_case(OP_METHOD_UNARY) {}
        opcode_case(OP_METHOD_BINARY) {}
        opcode_case(OP_METHOD_KEYWORD) {}

        opcode_case(OP_UNARY) {}
        opcode_case(OP_BINARY) {}
        opcode_case(OP_KEYWORD) {}
    }

    return chunk_new();
}
