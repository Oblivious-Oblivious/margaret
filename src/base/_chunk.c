#include "_chunk.h"

#include "memory.h"

#define CHUNK_GROW_FACTOR 1.618

static void chunk_ensure_space(chunk *self) {
    size_t new_capacity = self->alloced * CHUNK_GROW_FACTOR;
    uint8_t *new_items = (uint8_t*)collected_realloc(self->items, sizeof(uint8_t) * new_capacity);
    size_t *new_lines = (size_t*)collected_realloc(self->lines, sizeof(size_t) * new_capacity);

    if(new_items) {
        self->alloced = new_capacity;
        self->items = new_items;
    }
    if(new_lines)
        self->lines = new_lines;
}

chunk *chunk_new(void) {
    chunk *self = (chunk*)collected_malloc(sizeof(chunk));

    self->alloced = 32;
    self->size = 0;
    self->items = (uint8_t*)collected_malloc(sizeof(uint8_t) * self->alloced);
    self->lines = (size_t*)collected_malloc(sizeof(size_t) * self->alloced);
    self->temp_vector = temporaries_new();

    return self;
}

void chunk_add(chunk *self, uint8_t item, size_t line) {
    if(self->alloced == self->size)
        chunk_ensure_space(self);

    self->items[self->size] = item;
    self->lines[self->size] = line;
    self->size++;
}

uint32_t chunk_temporary_add(chunk *chunk, MargValue value) {
    temporaries_add(chunk->temp_vector, value);
    return temporaries_size(chunk->temp_vector) - 1;
}
