#include "MargMethod.h"

#include "MargString.h"
#include "MargTensor.h"

MargMethod *marg_method_new(VM *vm, MargObject *bound_object, char *message_name) {
    MargObject *obj = marg_object_new(vm, sizeof(MargMethod), "$Method");
    MargMethod *self = (MargMethod*)obj;

    self->bound_object = bound_object;

    self->message_name = MARG_STRING(message_name);
    self->parameter_names = MARG_TENSOR(2);
    self->proc = marg_proc_new(vm, self);

    return self;
}
