#include "instruction.h"

MargSymbol *marg_symbol_new(VM *vm, char *value) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargSymbol), G("$Symbol"), string_new("")
  );
  MargSymbol *self = (MargSymbol *)obj;

  self->value = string_new(value);

  return self;
}
