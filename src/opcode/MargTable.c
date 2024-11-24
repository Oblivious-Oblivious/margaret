#include "instruction.h"

MargTable *marg_table_new(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargTable), G("$Table"), string_new("")
  );
  MargTable *self = (MargTable *)obj;

  table_init(&self->value);

  return self;
}
