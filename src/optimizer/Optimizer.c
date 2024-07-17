#include "Optimizer.h"

#include "../opcode/MargProc.h" /* IWYU pragma: keep */
#include "../opcode/opcodes.h"

VM *optimizer_optimize(VM *vm) {
  vm->current->ip = vm->current->bytecode;

  while(true) {
    uint8_t instruction;
    switch(instruction = READ_BYTE()) {
    case OP_HALT: {
      return vm;
    }
    default: {
    }
    }
  }

  return vm;
}
