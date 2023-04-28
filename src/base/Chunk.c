#include "Chunk.h"

#include "memory.h"

#define CHUNK_GROW_FACTOR 1.618

static void chunk_ensure_space(Chunk *self) {
    uint8_t *new_items = (uint8_t*)collected_realloc(self->items, sizeof(uint8_t) * CHUNK_GROW_FACTOR);
    size_t *new_lines = (size_t*)collected_realloc(self->items, sizeof(size_t) * CHUNK_GROW_FACTOR);

    if(new_items) {
        self->alloced = self->alloced * CHUNK_GROW_FACTOR;
        self->items = new_items;
    }
    if(new_lines)
        self->lines = new_lines;
}

Chunk *chunk_new(void) {
    Chunk *self = (Chunk*)collected_malloc(sizeof(Chunk));

    self->alloced = 5000;
    self->size = 0;
    self->items = (uint8_t*)collected_malloc(sizeof(uint8_t) * self->alloced);
    self->lines = (size_t*)collected_malloc(sizeof(size_t) * self->alloced);
    self->constants = constants_new();

    return self;
}

void chunk_add(Chunk *self, uint8_t item, size_t line) {
    if(self->alloced == self->size)
        chunk_ensure_space(self);

    self->items[self->size] = item;
    self->lines[self->size] = line;
    self->size++;
}

uint32_t chunk_constant_add(Chunk *chunk, MargValue value) {
    constants_add(chunk->constants, value);
    return constants_size(chunk->constants) - 1;
}
