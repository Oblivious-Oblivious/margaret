#include "MargObject.h"

#include "../base/memory.h"

MargObject *marg_object_allocate(size_t size, MargObjectType type) {
    MargObject *self = (MargObject*)collected_malloc(sizeof(MargObject) * size);

    self->type = type;

    return self;
}
