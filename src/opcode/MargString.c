#include "MargString.h"

#include <string.h> /* memcpy, strlen */

#include "../base/fnv_1a_64_hash.h"

MargValue orphan_marg_string_new(VM *vm, char *chars) {
    size_t size = strlen(chars);
    MargString *self = (MargString*)(MargObject*)orphan_marg_object_new(vm, sizeof(MargString) + size, "");
    self->hash = fnv_1a_64_hash(chars, size);
    return QNAN_BOX(self);
}

MargString *marg_string_new(VM *vm, char *chars) {
    size_t size = strlen(chars);
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargString) + size + 1, "$String");
    MargString *self = (MargString*)obj;

    MargValue proto_object = table_get(&vm->global_variables, orphan_marg_string_new(vm, "$StringProto"));
    obj->parent = AS_OBJECT(proto_object);

    self->size = size;
    self->hash = fnv_1a_64_hash(chars, size);
    memcpy(self->chars, chars, size);
    self->chars[size] = '\0';

    return self;
}
