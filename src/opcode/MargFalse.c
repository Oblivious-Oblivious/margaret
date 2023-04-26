#include "MargFalse.h"

MargFalse *marg_false_new(void) {
    return (MargFalse*)marg_object_allocate(sizeof(MargFalse), MARG_FALSE_TYPE);
}
