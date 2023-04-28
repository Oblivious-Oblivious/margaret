#include "MargInteger.h"

MargInteger *marg_integer_new(int64_t value) {
    MargInteger *self = (MargInteger*)marg_object_allocate(sizeof(MargInteger), MARG_INTEGER_TYPE);

    self->value = value;

    return self;
}