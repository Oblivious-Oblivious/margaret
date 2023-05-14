#include "MargMethod.h"

MargMethod *marg_method_new(VM *vm, MargObject *bound_object, char *message_name) {
    MargObject *obj = marg_object_new(vm, sizeof(MargMethod), "$Method");
    MargMethod *self = (MargMethod*)obj;

    self->bound_object = bound_object;

    self->message_name = MARG_STRING(message_name);
    self->proc = marg_proc_new(vm, self);

    return self;
}
