#include "MargNil.h"

#include "MargString.h"

MargNil *marg_nil_new(VM *vm) {
    return AS_NIL(table_get(&vm->global_variables, MARG_STRING("$nil")));
}
