#include "Chunk.h"
#include <stdio.h>

#define CHUNK_GROW_FACTOR 1.618

// TODO Specialize marg_vector data from void* to a union of types for DRY

/**
 * @func: chunk_ensure_space
 * @desc: Ensure there is enough space for our values in the chunk
 * @param self -> The chunk to use
 * @param capacity -> The new capacity to set
 **/
static void chunk_ensure_space(Chunk *self, size_t capacity) {
    uint8_t *items = NULL;

    if(self == NULL || capacity == 0) {
        printf("ERROR: Not enough memory\n");
        exit(1);
    }

    /* Attempt to reallocate new memory in the items list */
    items = collected_realloc(self->bytecode, sizeof(uint8_t) * capacity);

    if(items) {
        /* Reset the items in the new memory space */
        self->bytecode = items;
        self->alloced = capacity;
    }
}

Chunk *chunk_new(void) {
    Chunk *self = (Chunk*)collected_malloc(sizeof(Chunk));
    self->alloced = 512;
    self->size = 0;
    self->bytecode = (uint8_t*)collected_malloc(sizeof(uint8_t) * self->alloced);
    return self;
}

Chunk *chunk_add(Chunk *self, uint8_t item) {
    if(self == NULL) return self;
    if(self->alloced == self->size)
        chunk_ensure_space(self, self->alloced * CHUNK_GROW_FACTOR);
    self->bytecode[self->size++] = item;

    return self;
}

uint8_t chunk_get(Chunk *self, size_t index) {
    if(self == NULL) return 0;
    if(index < self->size)
        return self->bytecode[index];

    return 0;
}

void chunk_set(Chunk *self, size_t index, uint8_t item) {
    if(self == NULL) return;
    if(index < self->size)
        self->bytecode[index] = item;
}

size_t chunk_size(Chunk *self) {
    if(self == NULL) return 0;
    return self->size;
}
