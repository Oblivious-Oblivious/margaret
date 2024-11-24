#include "instruction.h"

MargMethod *marg_method_new(
  VM *vm,
  MargObject *bound_object,
  MargMethod *bound_method,
  const char *message_name
) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargMethod), G("$Method"), string_new("")
  );
  MargMethod *self = (MargMethod *)obj;

  self->bound_object = bound_object;
  self->bound_method = bound_method;

  self->message_name = message_name;

  self->constants = NULL;
  table_init(&self->local_variables);
  self->local_index = 0;

  self->bytecode = NULL;
  self->ip       = -1;

  return self;
}
