#include "MargNil.h"

MargNil *marg_nil_new(void) {
    return (MargNil*)marg_pointer_new(sizeof(MargNil), MARG_NIL_TYPE);
}
