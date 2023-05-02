#include "MargInteger.h"

MargInteger *marg_integer_new(table *global_variables, int64_t value) {
    MargObject *obj = (MargObject*)marg_object_new(global_variables, sizeof(MargInteger), "$Integer", 9);
    MargInteger *self = (MargInteger*)obj;

    self->value = value;

    return self;
}
