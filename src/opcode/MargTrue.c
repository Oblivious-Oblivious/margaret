#include "MargTrue.h"

MargTrue *marg_true_new(void) {
    return (MargTrue*)marg_pointer_new(sizeof(MargTrue), MARG_TRUE_TYPE);
}
