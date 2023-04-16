#include "Optimizer.h"

#include "../base/memory.h"

#define opcode_case(opstr) if(opcode == opstr)

Optimizer *optimizer_new(Chunk *bytecode) {
    Optimizer *self = (Optimizer*)collected_malloc(sizeof(Optimizer));

    self->stack.top = -1;
    self->bytecode = bytecode;

    return self;
}

Chunk *optimizer_optimize(Optimizer *self) {
    size_t bytecode_size = chunk_size(self->bytecode);
    for(size_t ip = 0; ip < bytecode_size; ip++) {
        uint8_t opcode = chunk_get(self->bytecode, ip);

        // TODO Use actual opcodes
        opcode_case(0x0) {}
    }

    return chunk_new();
}
