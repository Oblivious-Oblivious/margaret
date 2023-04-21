#include "MargString.h"

#include <string.h> /* memcpy */

#include "../base/memory.h"

static ObjString *obj_string_allocate(char *chars, size_t size) {
    ObjString *string = (ObjString*)obj_allocate(sizeof(ObjString), OBJ_STRING);

    string->size = size;
    string->chars = chars;

    return string;
}

ObjString *obj_string_copy(char *chars, size_t size) {
    char *heap_chars = (char*)collected_malloc(sizeof(char) * size + 1);
    memcpy(heap_chars, chars, size);
    heap_chars[size] = '\0';
    return obj_string_allocate(heap_chars, size);
}
