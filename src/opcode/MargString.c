#include "MargString.h"

#include <string.h> /* memcpy */

#include "../base/memory.h"

static MargString *marg_string_allocate(char *chars, size_t size) {
    MargString *string = (MargString*)marg_object_allocate(sizeof(MargString), MARG_STRING);

    string->size = size;
    string->chars = chars;

    return string;
}

MargString *marg_string_copy(char *chars, size_t size) {
    char *heap_chars = (char*)collected_malloc(sizeof(char) * size + 1);
    memcpy(heap_chars, chars, size);
    heap_chars[size] = '\0';
    return marg_string_allocate(heap_chars, size);
}
