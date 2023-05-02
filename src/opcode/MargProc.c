#include "MargProc.h"

MargProc *marg_proc_new(table *global_variables, MargMethod *bound_method) {
    MargObject *obj = marg_object_new(global_variables, sizeof(MargProc), "$Proc", 6);
    MargProc *self = (MargProc*)obj;

    table_init(&self->parameters);
    self->bound_method = bound_method;
    self->code = activation_record_new(self);

    return self;
}
