#include "MargValue.h"

#include <float.h>  /* LDBL_DIG */

#include "../base/memory.h"

#include "MargInteger.h"
#include "MargFloat.h"
#include "MargString.h"

#include "MargTensor.h"
#include "MargHash.h"

#include "MargObject.h"
#include "MargMethod.h"
#include "MargProc.h"

string *marg_value_format(MargValue self) {
    if(IS_UNDEFINED(self))
        return string_new("<unbound>");
    else if(IS_INTEGER_CLONE(self))
        return string_new(marg_integer_to_string(self));
    else if(IS_FLOAT_CLONE(self))
        return string_new(marg_float_to_string(self));
    else if(IS_STRING_CLONE(self)) {
        string *res = string_new("");
        string_addf(res, "\"%s\"", AS_STRING(self)->chars);
        return res;
    }
    else if(IS_METHOD_CLONE(self))
        return string_new(marg_method_to_string(self));
    else if(IS_PROC_CLONE(self))
        return string_new(marg_proc_to_string(self));
    else if(IS_TENSOR_CLONE(self))
        return string_new(marg_tensor_to_string(self));
    else if(IS_HASH_CLONE(self))
        return string_new(marg_hash_to_string(self));
    else
        return string_new(AS_OBJECT(self)->name);
}

string *marg_value_as_variable(MargValue self) {
    string *res = string_new("");

    if(IS_STRING_CLONE(self))
        string_addf(res, "%s", AS_STRING(self)->chars);

    return res;
}
