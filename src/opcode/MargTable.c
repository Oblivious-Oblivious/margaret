#include "MargValue.h"

MargTable *marg_table_new(VM *vm) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargTable),
    table_get(&vm->global_variables, "$Enumerable"),
    string_new("$Table")
  );
  MargTable *self = (MargTable *)obj;

  table_init(&self->value);

  return self;
}
