#include "Constants.h"

#include "memory.h"

#define CONSTANTS_GROW_FACTOR 1.618

static void constants_ensure_space(Constants *self) {
    MargValue *new_items = (MargValue*)collected_realloc(self->items, sizeof(MargValue) * self->alloced * CONSTANTS_GROW_FACTOR);

    if(new_items) {
        self->alloced = self->alloced * CONSTANTS_GROW_FACTOR;
        self->items = new_items;
    }
}

Constants *constants_new(void) {
    Constants *self = (Constants*)collected_malloc(sizeof(Constants));

    self->alloced = 5000;
    self->size = 0;
    self->items = (MargValue*)collected_malloc(sizeof(MargValue) * self->alloced);

    return self;
}

void constants_add(Constants *self, MargValue item) {
    if(self->alloced == self->size)
        constants_ensure_space(self);

    self->items[self->size++] = item;
}
