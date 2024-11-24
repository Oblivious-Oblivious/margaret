#include "instruction.h"

MargTensor *marg_tensor_new(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargTensor), G("$Tensor"), string_new("")
  );
  MargTensor *self = (MargTensor *)obj;

  self->value = NULL;

  return self;
}
