#include "vector.h"

#include "memory.h"

#define VECTOR_GROW_FACTOR 1.618

#define VECTOR_DEFINE(structname, typename, type) \
    /**
     * @desc: Ensure there is enough space for our values in the vector
     * @param self -> The vector to use
     * @param capacity -> The new capacity to set
     **/ \
    static void typename##_ensure_space(structname *self, size_t capacity) { \
        if(self == NULL || capacity == 0) return; \
        \
        /* Attempt to reallocate new memory in the items list */ \
        self->alloced = capacity; \
        self->items = (type*)collected_realloc(self->items, sizeof(type) * self->alloced); \
        self->lines = (size_t*)collected_realloc(self->lines, sizeof(size_t) * self->alloced); \
    } \
    \
    structname *typename##_new_empty(void) { \
        structname *self = (structname*)collected_malloc(sizeof(structname)); \
        self->alloced = 512; \
        self->size = 0; \
        self->items = (type*)collected_malloc(sizeof(type) * self->alloced); \
        self->lines = (size_t*)collected_malloc(sizeof(size_t) * self->alloced); \
        self->constants = NULL; \
        \
        return self; \
    } \
    \
    structname *typename##_add(structname *self, type item) { \
        if(self == NULL) return self; \
        if(self->alloced == self->size) \
            typename##_ensure_space(self, self->alloced * VECTOR_GROW_FACTOR); \
        self->items[self->size++] = item; \
        \
        return self; \
    } \
    \
    type typename##_get(structname *self, size_t index) { \
        if(self == NULL) return 0; \
        if(index < self->size) \
            return self->items[index]; \
        \
        return 0; \
    } \
    \
    size_t typename##_size(structname *self) { \
        if(self == NULL) return 0; \
        return self->size; \
    }

VECTOR_DEFINE(vector, vector, void*)
VECTOR_DEFINE(ValueVector, value_vector, MargValue)
VECTOR_DEFINE(Chunk, chunk, uint8_t)

vector *__internal_vector_new(size_t argc, ...) {
    vector *self = (vector*)collected_malloc(sizeof(vector));
    self->alloced = 512;
    self->size = 0;
    self->items = (void**)collected_malloc(sizeof(void*) * self->alloced);
    self->lines = (size_t*)collected_malloc(sizeof(size_t) * self->alloced);
    self->constants = NULL;

    va_list vars;
    va_start(vars, argc);
        for(size_t i = 0; i < argc; i++)
            vector_add(self, va_arg(vars, void*));
    va_end(vars);

    return self;
}

uint8_t chunk_add_constant(Chunk *chunk, MargValue value) {
    if(chunk->constants == NULL) chunk->constants = value_vector_new_empty();

    value_vector_add(chunk->constants, value);
    return value_vector_size(chunk->constants) - 1;
}

uint32_t chunk_add_long_constant(Chunk *chunk, MargValue value) {
    if(chunk->constants == NULL) chunk->constants = value_vector_new_empty();

    value_vector_add(chunk->constants, value);
    return value_vector_size(chunk->constants) - 1;
}

MargValue chunk_get_constant(Chunk *chunk, size_t index) {
    return chunk->constants->items[index];
}

void chunk_add_with_line(Chunk *chunk, uint8_t byte, size_t line) {
    chunk->lines[chunk_size(chunk)] = line;
    chunk_add(chunk, byte);
}
