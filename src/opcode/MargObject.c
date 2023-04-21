#include "MargObject.h"

#include "../base/memory.h"

Obj* obj_allocate(size_t size, ObjType type) {
    Obj *object = (Obj*)collected_malloc(sizeof(Obj) * size);

    object->type = type;

    return object;
}
