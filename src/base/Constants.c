#include "Constants.h"

#include "memory.h"

#define CONSTANTS_GROW_FACTOR 1.618

static void constants_ensure_space(Constants *self) {
    size_t new_capacity = self->alloced * CONSTANTS_GROW_FACTOR;
    MargValue *items = (MargValue*)collected_realloc(self->items, sizeof(MargValue) * new_capacity);

    if(items) {
        self->alloced = new_capacity;
        self->items = items;
    }
}

Constants *constants_new(void) {
    Constants *self = (Constants*)collected_malloc(sizeof(Constants));

    self->alloced = 32;
    self->size = 0;
    self->items = (MargValue*)collected_malloc(sizeof(MargValue) * self->alloced);

    return self;
}

void constants_add(Constants *self, MargValue item) {
    if(self->alloced == self->size)
        constants_ensure_space(self);

    self->items[self->size++] = item;
}
