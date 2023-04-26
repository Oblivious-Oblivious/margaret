#include "MargNil.h"

MargNil *marg_nil_new(void) {
    return (MargNil*)marg_object_allocate(sizeof(MargNil), MARG_NIL_TYPE);
}
