#include "instruction.h"

MargFloat *marg_float_new(VM *vm, double value) {
  MargObject *obj =
    marg_object_new(vm, sizeof(MargFloat), G("$Float"), string_new(""));
  MargFloat *self = (MargFloat *)obj;

  self->value = value;

  return self;
}
