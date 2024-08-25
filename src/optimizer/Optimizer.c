#include "Optimizer.h"

#include "../opcode/MargProc.h"
#include "../opcode/opcodes.h"

VM *optimizer_optimize(VM *vm) {
  if(vm->has_error) {
    return vm;
  }

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
