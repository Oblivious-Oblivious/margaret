#include "MargNil.h"

MargNil *marg_nil_new(VM *vm) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargNil), "$nil", 5);
    MargNil *self = (MargNil*)obj;

    return self;
}
