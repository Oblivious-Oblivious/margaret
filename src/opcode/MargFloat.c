#include "MargFloat.h"

#include "MargValue.h"

#include <float.h> /* LDBL_DIG */

MargFloat *marg_float_new(VM *vm, double value) {
  MargObject *obj =
    (MargObject *)marg_object_new(vm, sizeof(MargFloat), "$FloatClone");
  MargFloat *self = (MargFloat *)obj;

  MargValue proto_object =
    table_get(&vm->global_variables, MARG_STRING("$Float"));
  obj->parent = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->value = value;

  return self;
}

char *marg_float_to_string(MargValue object) {
  string *res = string_new("");
  string_addf(res, "%.*Lg", LDBL_DIG, AS_FLOAT(object)->value);
  return string_get(res);
}
