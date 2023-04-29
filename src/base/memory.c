#include "memory.h"

// TODO Implement a rudimentary GC

void *collected_malloc(size_t nbytes) {
    return malloc(nbytes);
}

void *collected_realloc(void *old, size_t new_size) {
    return realloc(old, new_size);
}
