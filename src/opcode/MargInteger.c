#include "MargValue.h"

MargInteger *marg_integer_new(VM *vm, ptrdiff_t value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargInteger),
    table_get(&vm->global_variables, "$Numeric"),
    string_new("$Integer")
  );
  MargInteger *self = (MargInteger *)obj;

  self->value = value;

  return self;
}
