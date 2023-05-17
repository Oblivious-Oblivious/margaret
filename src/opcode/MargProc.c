#include "MargProc.h"

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
    MargObject *obj = marg_object_new(vm, sizeof(MargProc), "$Proc");
    MargProc *self = (MargProc*)obj;

    self->bound_method = bound_method;
    self->bound_proc = bound_method->proc;

    table_init(&self->parameters);
    self->global_variables = &self->bound_method->bound_object->bound_vm->global_variables;
    self->instance_variables = &self->bound_method->bound_object->instance_variables;
    table_init(&self->local_variables);

    self->bytecode = chunk_new();
    self->ip = self->bytecode->items;

    return self;
}
