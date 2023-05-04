#include "MargMethod.h"

MargMethod *marg_method_new(VM *vm, MargObject *bound_object) {
    MargObject *obj = marg_object_new(vm, sizeof(MargMethod), "$Method", 8);
    MargMethod *self = (MargMethod*)obj;

    self->bound_object = bound_object;

    self->proc = marg_proc_new(vm, self);

    return self;
}
