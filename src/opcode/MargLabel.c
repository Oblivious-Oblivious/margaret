#include "instruction.h"

MargLabel *marg_label_new(VM *vm, const char *name) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargLabel), G("$Label"), string_new("")
  );
  MargLabel *self = (MargLabel *)obj;

  self->name  = name;
  self->value = vector_size(vm->current->bytecode);

  return self;
}
