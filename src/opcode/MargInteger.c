#include "MargInteger.h"

#include "MargString.h"

MargInteger *marg_integer_new(VM *vm, int64_t value) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargInteger), "$Integer");
    MargInteger *self = (MargInteger*)obj;

    MargValue proto_object = table_get(&vm->global_variables, MARG_STRING("$IntegerProto"));
    obj->parent = AS_OBJECT(proto_object);

    self->value = value;

    return self;
}
