#include "MargInteger.h"

MargInteger *marg_integer_new(VM *vm, int64_t value) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargInteger), "$Integer");
    MargInteger *self = (MargInteger*)obj;

    self->value = value;

    return self;
}
