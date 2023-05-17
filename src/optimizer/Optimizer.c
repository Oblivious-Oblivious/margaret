#include "Optimizer.h"

#include "../opcode/opcodes.h"

#include "../opcode/MargProc.h"

VM *optimizer_optimize(VM *vm) {
    vm->current->ip = vm->current->bytecode->items;

    // TODO Branch table, computed goto
    while(1) {
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OP_HALT: {
                return vm;
            }
            default: {}
        }
    }

    return vm;
}
