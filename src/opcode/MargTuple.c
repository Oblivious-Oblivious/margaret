#include "MargValue.h"

MargTuple *marg_tuple_new(VM *vm) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargTuple),
    table_get(&vm->global_variables, "$Tensor"),
    string_new("$Tuple")
  );
  MargTuple *self = (MargTuple *)obj;

  self->value = NULL;

  return self;
}
