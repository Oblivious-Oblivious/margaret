#include "MargValue.h"

MargMethod *
marg_method_new(VM *vm, MargObject *bound_object, char *message_name) {
  MargObject *obj =
    marg_object_new(vm, sizeof(MargMethod), string_new("$MethodClone"));
  MargMethod *self = (MargMethod *)obj;

  MargValue proto_object = table_get(&vm->global_variables, "$Method");
  obj->parent            = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->bound_object = bound_object;
  /* self->bound_method = bound_method; */

  self->message_name    = AS_STRING(MARG_STRING(message_name));
  self->parameter_names = AS_TENSOR(MARG_TENSOR(2));
  self->temporaries     = NULL;
  table_init(&self->local_variables);

  self->bytecode = NULL;
  self->ip       = self->bytecode;
  self->sp       = self->bytecode;

  self->proc = marg_proc_new(vm, self); /* TODO - Remove */

  return self;
}

char *marg_method_to_string(MargMethod *object) {
  char *res = string_new("");
  string_addf(
    &res, "< %s#%s >", object->bound_object->name, object->message_name->value
  );
  return res;
}
