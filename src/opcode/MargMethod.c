#include "MargMethod.h"

#include "MargValue.h"

MargMethod *
marg_method_new(VM *vm, MargObject *bound_object, char *message_name) {
  MargObject *obj  = marg_object_new(vm, sizeof(MargMethod), "$MethodClone");
  MargMethod *self = (MargMethod *)obj;

  MargValue proto_object =
    table_get(&vm->global_variables, MARG_STRING("$Method"));
  obj->parent = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->bound_object = bound_object;

  self->message_name    = MARG_STRING(message_name);
  self->parameter_names = AS_TENSOR(MARG_TENSOR(2));
  self->proc            = marg_proc_new(vm, self);

  return self;
}

char *marg_method_to_string(MargMethod *object) {
  string *res = string_new("");
  string_addf(
    res,
    "< %s#%s >",
    object->bound_object->name,
    AS_STRING(object->message_name)->chars
  );
  return string_get(res);
}
