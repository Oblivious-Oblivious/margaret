#include "instruction.h"

MargTuple *marg_tuple_new(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargTuple), G("$Tuple"), string_new("")
  );
  MargTuple *self = (MargTuple *)obj;

  self->value = NULL;

  return self;
}
