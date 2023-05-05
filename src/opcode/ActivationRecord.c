#include "ActivationRecord.h"

#include "../base/memory.h"

ActivationRecord *activation_record_new(MargProc *bound_proc) {
    ActivationRecord *self = (ActivationRecord*)collected_malloc(sizeof(ActivationRecord));

    self->bound_proc = bound_proc;
    self->global_variables = &bound_proc->bound_method->bound_object->bound_vm->global_variables;
    self->instance_variables = &bound_proc->bound_method->bound_object->instance_variables;
    table_init(&self->local_variables);

    self->bytecode = chunk_new();
    self->ip = self->bytecode->items;

    return self;
}
