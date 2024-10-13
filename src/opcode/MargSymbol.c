#include "MargObject.h"
#include "MargValue.h"

MargSymbol *marg_symbol_new(VM *vm, char *value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargSymbol),
    table_get(&vm->global_variables, "$Symbol"),
    string_new("$Symbol")
  );
  MargSymbol *self = (MargSymbol *)obj;

  self->value = value;

  return self;
}

char *marg_symbol_to_string(MargSymbol *object) {
  char *res = string_new("");
  string_addf(&res, "%s", object->value);
  return res;
}
