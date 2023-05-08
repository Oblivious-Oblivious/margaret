#include "MargProc.h"

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
    MargObject *obj = marg_object_new(vm, sizeof(MargProc), "$Proc");
    MargProc *self = (MargProc*)obj;

    self->bound_method = bound_method;

    table_init(&self->parameters);

    return self;
}
