#include "MargValue.h"

MargMethod *
marg_method_new(VM *vm, MargValue bound_object, char *message_name) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargMethod),
    table_get(&vm->global_variables, "$Margaret"),
    string_new("$Method")
  );
  MargMethod *self = (MargMethod *)obj;

  self->bound_object = AS_OBJECT(bound_object);
  self->bound_method = NULL;

  self->message_name = message_name;
  self->arguments    = NULL;
  self->constants    = NULL;
  table_init(&self->local_variables);
  self->bytecode = NULL;

  self->ip = self->bytecode;
  self->sp = self->bytecode;

  return self;
}
