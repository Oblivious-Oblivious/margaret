#include "MargProc.h"

#include "MargValue.h"

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
  MargObject *obj = marg_object_new(vm, sizeof(MargProc), "$ProcClone");
  MargProc *self  = (MargProc *)obj;

  MargValue proto_object =
    table_get(&vm->global_variables, MARG_STRING("$Proc"));
  obj->parent = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->bound_method = bound_method;
  self->bound_proc   = bound_method->proc;

  table_init(&self->parameters);
  table_init(&self->local_variables);

  self->bytecode = chunk_new();
  self->ip       = self->bytecode->items;

  return self;
}

char *marg_proc_to_string(MargProc *object) {
  EmeraldsString *res = string_new("");
  string_addf(res, "< %s:proc >", object->bound_method->bound_object->name);
  return string_get(res);
}
