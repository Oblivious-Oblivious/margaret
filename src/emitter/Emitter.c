#include "Emitter.h"

#include "../opcode/Opcodes.h"

#include "../base/memory.h"

#define opcode_case(opstr) if(marg_string_equals(opcode, (opstr)))

Emitter *emitter_new(marg_vector *bytecode) {
    Emitter *self = (Emitter*)collected_malloc(sizeof(Emitter));

    self->stack.top = -1;
    self->bytecode = bytecode;

    return self;
}

Chunk *emitter_emit(Emitter *self) {
    Chunk *bytecode = chunk_new_empty();

    size_t bytecode_size = marg_vector_size(self->bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        marg_string *opcode = marg_vector_get(self->bytecode, ip);

        opcode_case(FM_NIL) {}
        opcode_case(FM_TRUE) {}
        opcode_case(FM_FALSE) {}

        opcode_case(FM_SELF) {}
        opcode_case(FM_SUPER) {}

        opcode_case(FM_0) {}
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

    return bytecode;
}
