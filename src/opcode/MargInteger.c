#include "MargInteger.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "MargValue.h"

MargInteger *marg_integer_new(VM *vm, int64_t value) {
  MargObject *obj =
    (MargObject *)marg_object_new(vm, sizeof(MargInteger), "$IntegerClone");
  MargInteger *self = (MargInteger *)obj;

  MargValue proto_object =
    table_get(&vm->global_variables, MARG_STRING("$Integer"));
  obj->parent = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->value = value;

  return self;
}

char *marg_integer_to_string(MargInteger *object) {
  char *res = string_new("");
  string_addf(res, "%lld", object->value);
  return res;
}
