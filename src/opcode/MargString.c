#include "MargString.h"

#include <string.h> /* memcpy */

uint64_t marg_string_hash(char *key, size_t size) {
    uint64_t hash = 14695981039346656037u;

    for(size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 1099511628211;
    }

    return hash;
}

MargString *marg_string_new(char *chars, size_t size) {
    MargString *self = (MargString*)marg_pointer_new(sizeof(MargString) + size + 1, MARG_STRING_TYPE);

    self->size = size;
    self->hash = marg_string_hash(chars, size);
    memcpy(self->chars, chars, size);
    self->chars[size] = '\0';

    return self;
}
