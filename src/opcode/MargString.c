#include "MargValue.h"

MargString *marg_string_new(VM *vm, const char *value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargString),
    table_get(&vm->global_variables, "$String"),
    string_new("$String")
  );
  MargString *self = (MargString *)obj;

  self->value = string_new(value);

  return self;
}

char *marg_string_to_string(MargString *object) {
  char *res = string_new("");
  string_addf(&res, "\"%s\"", object->value);
  return res;
}
