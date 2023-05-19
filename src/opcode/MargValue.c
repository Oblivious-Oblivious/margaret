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
    else if(IS_INTEGER(self))
        return string_new(marg_integer_to_string(self));
    else if(IS_FLOAT(self))
        return string_new(marg_float_to_string(self));
    else if(IS_STRING(self)) {
        string *res = string_new("");
        string_addf(res, "\"%s\"", AS_STRING(self)->chars);
        return res;
    }
    else if(IS_METHOD(self))
        return string_new(marg_method_to_string(self));
    else if(IS_PROC(self))
        return string_new(marg_proc_to_string(self));
    else if(IS_TENSOR(self))
        return string_new(marg_tensor_to_string(self));
    else if(IS_HASH(self))
        return string_new(marg_hash_to_string(self));
    else
        return string_new(AS_OBJECT(self)->name);
}

string *marg_value_as_variable(MargValue self) {
    string *res = string_new("");

    if(IS_STRING(self))
        string_addf(res, "%s", AS_STRING(self)->chars);

    return res;
}
