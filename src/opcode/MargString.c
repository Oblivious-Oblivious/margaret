#include "MargString.h"

#include <string.h> /* memcpy */

#include "../base/memory.h"
#include "MargHash.h"
#include "MargValue.h"

uint64_t marg_string_hash(char *key, size_t size) {
    uint64_t hash = 14695981039346656037u;

    for(size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 1099511628211;
    }

    return hash;
}

static MargString *marg_string_allocate(size_t size, uint64_t hash) {
    MargString *string = (MargString*)marg_object_allocate(sizeof(MargString) + size + 1, MARG_STRING_TYPE);

    string->size = size;
    string->hash = hash;

    return string;
}

MargString *marg_string_new(char *chars, size_t size) {
    uint64_t hash = marg_string_hash(chars, size);
    MargString *self = marg_string_allocate(size, hash);

    memcpy(self->chars, chars, size);
    self->chars[size] = '\0';

    return self;
}
