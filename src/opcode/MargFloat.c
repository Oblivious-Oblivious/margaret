#include "MargFloat.h"

MargFloat *marg_float_new(double value) {
    MargFloat *self = (MargFloat*)marg_pointer_new(sizeof(MargFloat), MARG_FLOAT_TYPE);

    self->value = value;

    return self;
}
