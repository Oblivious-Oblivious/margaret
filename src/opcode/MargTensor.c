#include "MargValue.h"

MargTensor *marg_tensor_new(VM *vm) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargTensor),
    table_get(&vm->global_variables, "$Enumerable"),
    string_new("$Tensor")
  );
  MargTensor *self = (MargTensor *)obj;

  self->value = NULL;

  return self;
}
