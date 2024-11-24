#include "Optimizer.h"

#include "../opcode/MargMethod.h"
#include "../opcode/opcodes.h"

VM *optimizer_optimize(VM *vm) {
  if(vm->error) {
    goto exit;
  }

exit:
  return vm;
}
