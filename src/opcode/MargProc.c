#include "MargProc.h"

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
    MargObject *obj = marg_object_new(vm, sizeof(MargProc), "$Proc", 6);
    MargProc *self = (MargProc*)obj;

    table_init(&self->parameters);
    self->bound_method = bound_method;
    self->code = activation_record_new(self);

    return self;
}
