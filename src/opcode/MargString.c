#include "MargString.h"

#include <string.h> /* memcpy */

#include "../base/fnv_1a_64_hash.h"

MargString *marg_string_new(char *chars, size_t size) {
    MargString *self = (MargString*)marg_pointer_new(sizeof(MargString) + size + 1, MARG_STRING_TYPE);

    self->size = size;
    self->hash = fnv_1a_64_hash(chars, size);
    memcpy(self->chars, chars, size);
    self->chars[size] = '\0';

    return self;
}
