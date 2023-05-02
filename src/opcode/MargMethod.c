#include "MargMethod.h"

MargMethod *marg_method_new(table *global_variables, MargObject *bound_object) {
    MargObject *obj = marg_object_new(global_variables, sizeof(MargMethod), "$Method", 8);
    MargMethod *self = (MargMethod*)obj;

    self->bound_object = bound_object;

    return self;
}
