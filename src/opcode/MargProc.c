#include "MargProc.h"

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
    MargObject *obj = marg_object_new(vm, sizeof(MargProc), "$Proc", 6);
    MargProc *self = (MargProc*)obj;

    self->bound_method = bound_method;

    table_init(&self->parameters);
    self->activation_record = activation_record_new(self);

    return self;
}
