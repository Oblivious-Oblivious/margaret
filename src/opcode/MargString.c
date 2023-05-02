#include "MargString.h"

#include <string.h> /* memcpy */

#include "../base/fnv_1a_64_hash.h"

MargString *marg_string_new(VM *vm, char *chars, size_t size) {
    MargObject *obj = (MargObject*)marg_object_new(vm, sizeof(MargString) + size + 1, "$String", 8);
    MargString *self = (MargString*)obj;

    self->size = size;
    self->hash = fnv_1a_64_hash(chars, size);
    memcpy(self->chars, chars, size);
    self->chars[size] = '\0';

    return self;
}
