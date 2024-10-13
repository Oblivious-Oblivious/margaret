#include "MargValue.h"

MargInteger *marg_integer_new(VM *vm, ptrdiff_t value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargInteger),
    table_get(&vm->global_variables, "$Integer"),
    string_new("$Integer")
  );
  MargInteger *self = (MargInteger *)obj;

  self->value = value;

  return self;
}

char *marg_integer_to_string(MargInteger *object) {
  char *res = string_new("");
  string_addf(&res, "%lld", object->value);
  return res;
}
