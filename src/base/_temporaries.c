#include "_temporaries.h"

#include "memory.h"

#define TEMPORARIES_GROW_FACTOR 1.618

static void temporaries_ensure_space(temporaries *self) {
    size_t new_capacity = self->alloced * TEMPORARIES_GROW_FACTOR;
    MargValue *items = (MargValue*)collected_realloc(self->items, sizeof(MargValue) * new_capacity);

    if(items) {
        self->alloced = new_capacity;
        self->items = items;
    }
}

temporaries *temporaries_new(void) {
    temporaries *self = (temporaries*)collected_malloc(sizeof(temporaries));

    self->alloced = 32;
    self->size = 0;
    self->items = (MargValue*)collected_malloc(sizeof(MargValue) * self->alloced);

    return self;
}

void temporaries_add(temporaries *self, MargValue item) {
    if(self->alloced == self->size)
        temporaries_ensure_space(self);

    self->items[self->size++] = item;
}
