#include "MargFalse.h"

MargFalse *marg_false_new(table *global_variables) {
    MargObject *obj = marg_object_new(global_variables, sizeof(MargFalse), "$false", 7);
    MargFalse *self = (MargFalse*)obj;

    return self;
}
