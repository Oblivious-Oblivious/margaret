#include "MargObject.h"

#include "../base/memory.h"

MargObject *marg_object_allocate(size_t size, MargObjectType type) {
    MargObject *object = (MargObject*)collected_malloc(sizeof(MargObject) * size);

    object->type = type;

    return object;
}
