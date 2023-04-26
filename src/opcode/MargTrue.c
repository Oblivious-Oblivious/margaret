#include "MargTrue.h"

MargTrue *marg_true_new(void) {
    return (MargTrue*)marg_object_allocate(sizeof(MargTrue), MARG_TRUE_TYPE);
}
