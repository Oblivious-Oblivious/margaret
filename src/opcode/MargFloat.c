#include "MargValue.h"

#include <float.h> /* LDBL_DIG */

MargFloat *marg_float_new(VM *vm, double value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargFloat),
    table_get(&vm->global_variables, "$FloatProto"),
    "$Float"
  );
  MargFloat *self = (MargFloat *)obj;

  self->value = value;

  return self;
}

char *marg_float_to_string(MargFloat *object) {
  char *res = string_new("");
  string_addf(&res, "%.*Lg", LDBL_DIG, object->value);
  return res;
}
