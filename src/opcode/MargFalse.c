#include "MargFalse.h"

MargFalse *marg_false_new(void) {
    return (MargFalse*)marg_pointer_new(sizeof(MargFalse), MARG_FALSE_TYPE);
}
