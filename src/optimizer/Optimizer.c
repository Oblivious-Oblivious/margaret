#include "Optimizer.h"

#include "../opcode/Opcodes.h"

VM *optimizer_optimize(VM *vm) {
    vm->current->ip = vm->current->bytecode->items;

    // TODO Branch table, computed goto
    while(1) {
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OP_RETURN: {
                return vm;
            }
            default: {}
        }
    }

    return vm;
}
