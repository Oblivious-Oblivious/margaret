#include "memory.h"

#include "../../libs/boehm_gc/bdwgc/gc.h"

// TODO Implement a rudimentary GC

void *collected_malloc(size_t nbytes) {
    return malloc(nbytes);
    // return GC_MALLOC(nbytes);
}

void *collected_realloc(void *old, size_t new_size) {
    return realloc(old, new_size);
    // return GC_REALLOC(old, new_size);
}
