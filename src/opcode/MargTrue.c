#include "MargTrue.h"

MargTrue *marg_true_new(table *global_variables) {
    MargObject *obj = (MargObject*)marg_object_new(global_variables, sizeof(MargTrue), "$true", 6);
    MargTrue *self = (MargTrue*)obj;

    return self;
}
