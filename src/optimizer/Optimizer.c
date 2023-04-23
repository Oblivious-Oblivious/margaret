#include "Optimizer.h"

#include "../opcode/Opcodes.h"

VM *optimizer_optimize(VM *self) {
    self->ip = self->bytecode->items;

    // TODO Branch table, computed goto
    while(1) {
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OP_RETURN: {
                return self;
            }
            default: {}
        }
    }

    return self;
}
