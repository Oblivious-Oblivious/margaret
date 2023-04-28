#include "vector.h"

#include "memory.h"

#define VECTOR_GROW_FACTOR 1.618

/**
 * @desc: Ensure there is enough space for our values in the vector
 * @param self -> The vector to use
 * @param capacity -> The new capacity to set
 **/
static void vector_ensure_space(vector *self, size_t capacity) {
    if(self == NULL || capacity == 0) return;

    /* Attempt to reallocate new memory in the items list */
    self->alloced = capacity;
    void **new_items = (void**)collected_realloc(self->items, sizeof(void*) * self->alloced);

    if(new_items)
        self->items = new_items;
}

vector *__internal_vector_new(size_t argc, ...) {
    vector *self = vector_new_empty();

    va_list vars;
    va_start(vars, argc);
        for(size_t i = 0; i < argc; i++)
            vector_add(self, va_arg(vars, void*));
    va_end(vars);

    return self;
}

vector *vector_new_empty(void) {
    vector *self = (vector*)collected_malloc(sizeof(vector));

    self->alloced = 32;
    self->size = 0;
    self->items = (void**)collected_malloc(sizeof(void*) * self->alloced);

    return self;
}

vector *vector_add(vector *self, void *item) {
    if(self == NULL)
        return self;

    if(self->alloced == self->size)
        vector_ensure_space(self, self->alloced * VECTOR_GROW_FACTOR);
    self->items[self->size++] = item;

    return self;
}

void *vector_get(vector *self, size_t index) {
    if(self == NULL)
        return NULL;
    else if(index < self->size)
        return self->items[index];
    else
        return NULL;
}

size_t vector_size(vector *self) {
    if(self == NULL)
        return 0;
    else
        return self->size;
}
