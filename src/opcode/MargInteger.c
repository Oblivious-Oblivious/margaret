#include "instruction.h"

MargInteger *marg_integer_new(VM *vm, ptrdiff_t value) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargInteger), G("$Integer"), string_new("")
  );
  MargInteger *self = (MargInteger *)obj;

  self->value = value;

  return self;
}
