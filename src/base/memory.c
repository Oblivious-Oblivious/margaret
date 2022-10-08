#include "memory.h"

#include "../../libs/boehm_gc/bdwgc/gc.h"

void *collected_malloc(size_t nbytes) {
    return GC_MALLOC(nbytes);
}

void *collected_realloc(void *old, size_t new_size) {
    return GC_REALLOC(old, new_size);
}
