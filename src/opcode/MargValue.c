#include "MargValue.h"

#include <math.h>   /* floor */
#include <float.h>  /* LDBL_DIG */

#include "../base/memory.h"

#include "MargNil.h"
#include "MargTrue.h"
#include "MargFalse.h"

#include "MargInteger.h"
#include "MargFloat.h"
#include "MargString.h"

#include "MargObject.h"
#include "MargMethod.h"
#include "MargProc.h"

string *marg_value_format(MargValue self) {
    string *res = string_new("");

    if(IS_UNDEFINED(self))
        string_add_str(res, "$nil");

    else if(IS_NIL(self))
        string_add_str(res, "$nil");
    else if(IS_FALSE(self))
        string_add_str(res, "$false");
    else if(IS_TRUE(self))
        string_add_str(res, "$true");

    else if(IS_INTEGER(self))
        string_addf(res, "%lld", AS_INTEGER(self)->value);
    else if(IS_FLOAT(self))
        string_addf(res, "%.*Lg", LDBL_DIG, AS_FLOAT(self)->value);
    else if(IS_STRING(self))
        string_addf(res, "\"%s\"", AS_STRING(self)->chars);

    else if(IS_OBJECT(self))
        string_add_str(res, AS_OBJECT(self)->name);
    else if(IS_METHOD(self))
        string_add_str(res, "<method>");
    else if(IS_PROC(self))
        string_add_str(res, "<proc>");

    else
        string_add_str(res, "Undefined");

    return res;
}

string *marg_value_as_variable(MargValue self) {
    string *res = string_new("");

    if(IS_STRING(self))
        string_addf(res, "%s", AS_STRING(self)->chars);

    return res;
}
