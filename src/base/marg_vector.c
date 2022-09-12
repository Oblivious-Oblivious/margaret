#include "marg_vector.h"

#define GROW_FACTOR 1.618

/**
 * @func: marg_vector_ensure_space
 * @desc: Ensure there is enough space for our values in the vector
 * @param self -> The vector to use
 * @param capacity -> The new capacity to set
 **/
static void marg_vector_ensure_space(marg_vector *self, size_t capacity) {
    void **items = NULL;

    if(self == NULL || capacity == 0) return;

    /* Attempt to reallocate new memory in the items list */
    items = realloc(self->items, sizeof(void*) * capacity);

    if(items) {
        /* Reset the items in the new memory space */
        self->items = items;
        self->alloced = capacity;
    }
}

marg_vector *marg_vector_new(void) {
    marg_vector *self = (marg_vector*)malloc(sizeof(marg_vector));
    self->alloced = 32;
    self->size = 0;
    self->items = (void**)malloc(sizeof(void*) * self->alloced);
    return self;
}

marg_vector *marg_vector_add(marg_vector *self, void *item) {
    if(self == NULL) return self;
    if(self->alloced == self->size)
        marg_vector_ensure_space(self, self->alloced * GROW_FACTOR);
    self->items[self->size++] = item;

    return self;
}

void *marg_vector_get(marg_vector *self, size_t index) {
    if(self == NULL) return NULL;
    if(index < self->size)
        return self->items[index];

    return NULL;
}

size_t marg_vector_size(marg_vector *self) {
    if(self == NULL) return 0;
    return self->size;
}

void marg_vector_free(marg_vector *self) {
    /* TODO Add a free iteration for each MargValue element */
    if(self != NULL && self->items != NULL)
        free(self->items);
    if(self != NULL)
        free(self);
}