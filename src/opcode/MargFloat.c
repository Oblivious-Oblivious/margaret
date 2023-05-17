#include "MargFloat.h"

#include "MargString.h"

MargFloat *marg_float_new(VM *vm, double value) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargFloat), "$Float");
    MargFloat *self = (MargFloat*)obj;

    MargValue proto_object = table_get(&vm->global_variables, MARG_STRING("$FloatProto"));
    obj->parent = AS_OBJECT(proto_object);
    table_set(&obj->instance_variables, MARG_STRING("@super"), proto_object);

    self->value = value;

    return self;
}
