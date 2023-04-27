#include "MargFloat.h"

MargFloat *marg_float_new(double value) {
    MargFloat *self = (MargFloat*)marg_object_allocate(sizeof(MargFloat), MARG_FLOAT_TYPE);

    self->value = value;

    return self;
}
