#include "MargFloat.h"

MargFloat *marg_float_new(table *global_variables, double value) {
    MargObject *obj = (MargObject*)marg_object_new(global_variables, sizeof(MargFloat), "$Float", 7);
    MargFloat *self = (MargFloat*)obj;

    self->value = value;

    return self;
}
