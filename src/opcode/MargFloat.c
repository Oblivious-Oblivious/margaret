#include "MargFloat.h"

MargFloat *marg_float_new(VM *vm, double value) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargFloat), "$Float");
    MargFloat *self = (MargFloat*)obj;

    self->value = value;

    return self;
}
