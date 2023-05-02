#include "ActivationRecord.h"

#include "../base/memory.h"

ActivationRecord *activation_record_new(MargProc *bound_proc) {
    ActivationRecord *self = (ActivationRecord*)collected_malloc(sizeof(ActivationRecord));

    self->bytecode = chunk_new();
    table_init(&self->local_variables);
    self->bound_proc = bound_proc;
    self->instance_variables = &bound_proc->bound_method->bound_object->instance_variables;
    self->global_variables = &bound_proc->bound_method->bound_object->bound_vm->global_variables;

    return self;
}
