#include "temporaries.h"

temporaries *temporaries_new(void) {
    temporaries *self = (temporaries*)collected_malloc(sizeof(temporaries));

    self->alloced = 32;
    self->size = 0;
    self->items = (MargValue*)collected_malloc(sizeof(MargValue) * self->alloced);

    return self;
}
