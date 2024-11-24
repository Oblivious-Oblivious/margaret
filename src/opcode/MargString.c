#include "instruction.h"

MargString *marg_string_new(VM *vm, const char *value) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargString), G("$String"), string_new("")
  );
  MargString *self = (MargString *)obj;

  self->value = string_new(value);

  return self;
}
