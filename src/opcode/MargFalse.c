#include "MargFalse.h"

#include "MargString.h"

MargFalse *marg_false_new(VM *vm) {
    return AS_FALSE(table_get(&vm->global_variables, MARG_STRING("$false")));
}
