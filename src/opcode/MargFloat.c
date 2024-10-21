#include "MargValue.h"

#include <float.h> /* LDBL_DIG */

MargFloat *marg_float_new(VM *vm, double value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargFloat),
    table_get(&vm->global_variables, "$Numeric"),
    string_new("$Float")
  );
  MargFloat *self = (MargFloat *)obj;

  self->value = value;

  return self;
}
