#include "MargTensor.h"

#include "../opcode/MargString.h"

MargTensor *marg_tensor_new(VM *vm, size_t initial_alloced) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargTensor), "$Tensor");
    MargTensor *self = (MargTensor*)obj;

    MargValue proto_object = table_get(&vm->global_variables, MARG_STRING("$TensorProto"));
    obj->parent = AS_OBJECT(proto_object);

    self->alloced = initial_alloced;
    self->size = 0;
    self->items = (MargValue*)collected_malloc(sizeof(MargValue) * self->alloced);

    return self;
}
