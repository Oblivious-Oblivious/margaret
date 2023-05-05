#include "MargNil.h"

MargNil *marg_nil_new(VM *vm) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargNil), "$nil");
    MargNil *self = (MargNil*)obj;

    return self;
}
