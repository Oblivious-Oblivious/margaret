#include "MargFalse.h"

MargFalse *marg_false_new(VM *vm) {
    MargObject *obj = marg_object_new(vm, sizeof(MargFalse), "$false");
    MargFalse *self = (MargFalse*)obj;

    return self;
}
