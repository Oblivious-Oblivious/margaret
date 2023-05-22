#include "MargFloat.h"

#include <float.h>  /* LDBL_DIG */

#include "MargString.h"

MargFloat *marg_float_new(VM *vm, double value) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargFloat), "$Float");
    MargFloat *self = (MargFloat*)obj;

    MargValue proto_object = table_get(&vm->global_variables, MARG_STRING("$FloatProto"));
    obj->parent = AS_OBJECT(proto_object);

    table_set(&obj->instance_variables, MARG_STRING("@self"), QNAN_BOX(obj));
    table_set(&obj->instance_variables, MARG_STRING("@super"), QNAN_BOX(obj->parent));

    self->value = value;

    return self;
}

char *marg_float_to_string(MargValue object) {
    string *res = string_new("");
    string_addf(res, "%.*Lg", LDBL_DIG, AS_FLOAT(object)->value);
    return string_get(res);
}
