#include "Optimizer.h"

#include "../opcode/MargMethod.h"
#include "../opcode/opcodes.h"

VM *optimizer_optimize(VM *vm) {
  if(vm->error) {
    goto exit;
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

exit:
  return vm;
}
