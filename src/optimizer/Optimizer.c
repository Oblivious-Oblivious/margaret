#include "Optimizer.h"

VM *optimizer_optimize(VM *vm) {
  if(vm->error) {
    goto exit;
  }

exit:
  return vm;
}
