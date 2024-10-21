#include "MargObject.h"
#include "MargValue.h"

MargSymbol *marg_symbol_new(VM *vm, char *value) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargSymbol),
    table_get(&vm->global_variables, "$String"),
    string_new("$Symbol")
  );
  MargSymbol *self = (MargSymbol *)obj;

  self->value = value;

  return self;
}
