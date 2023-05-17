#include "MargTrue.h"

#include "MargString.h"

MargTrue *marg_true_new(VM *vm) {
    return AS_TRUE(table_get(&vm->global_variables, MARG_STRING("$true")));
}
