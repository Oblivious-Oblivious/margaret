#include "MargTrue.h"

MargTrue *marg_true_new(VM *vm) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargTrue), "$true", 6);
    MargTrue *self = (MargTrue*)obj;

    return self;
}
