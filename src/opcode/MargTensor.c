#include "MargTensor.h"

MargTensor *marg_tensor_new(VM *vm, size_t initial_alloced) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargTensor), "$Tensor");
    MargTensor *self = (MargTensor*)obj;

    self->alloced = initial_alloced;
    self->size = 0;
    self->items = (MargValue*)collected_malloc(sizeof(MargValue) * self->alloced);

    return self;
}
