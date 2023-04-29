#include "MargPointer.h"

#include "../base/memory.h"

MargPointer *marg_pointer_new(size_t size, MargPointerType type) {
    MargPointer *self = (MargPointer*)collected_malloc(sizeof(MargPointer) * size);

    self->type = type;

    return self;
}
