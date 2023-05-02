#include "MargNil.h"

MargNil *marg_nil_new(table *global_variables) {
    MargObject *obj = (MargObject*)marg_object_new(global_variables, sizeof(MargNil), "$nil", 5);
    MargNil *self = (MargNil*)obj;

    return self;
}
