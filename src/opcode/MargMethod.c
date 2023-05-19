#include "MargMethod.h"

#include "MargString.h"
#include "MargTensor.h"

MargMethod *marg_method_new(VM *vm, MargObject *bound_object, char *message_name) {
    MargObject *obj = marg_object_new(vm, sizeof(MargMethod), "$Method");
    MargMethod *self = (MargMethod*)obj;

    MargValue proto_object = table_get(&vm->global_variables, MARG_STRING("$MethodProto"));
    obj->parent = AS_OBJECT(proto_object);

    self->bound_object = bound_object;

    self->message_name = MARG_STRING(message_name);
    self->parameter_names = MARG_TENSOR(2);
    self->proc = marg_proc_new(vm, self);

    return self;
}

char *marg_method_to_string(MargValue object) {
    string *res = string_new("");
    string_addf(res, "< %s#%s >", AS_METHOD(object)->bound_object->name, AS_STRING(AS_METHOD(object)->message_name)->chars);
    return string_get(res);
}
