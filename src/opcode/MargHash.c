#include "MargValue.h"

MargHash *marg_hash_new(VM *vm) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargHash),
    table_get(&vm->global_variables, "$Enumerable"),
    string_new("$Hash")
  );
  MargHash *self = (MargHash *)obj;

  table_init(&self->value);

  return self;
}
