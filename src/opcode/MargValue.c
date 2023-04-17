#include "MargValue.h"

marg_string *marg_value_format(MargValue self) {
    marg_string *res = marg_string_new("");
    marg_string_addf(res, "%g", self);
    return res;
}
