#include "MargObject.h"

#include "../base/memory.h"

#include <string.h> /* strlen */

MargObject *marg_object_new(VM *bound_vm, size_t size, char *name) {
    MargObject *self = (MargObject*)collected_malloc(sizeof(MargObject) * size);

    self->is_marked = false;
    self->next = NULL;

    self->bound_vm = bound_vm;

    self->name = (char*)malloc(sizeof(char) * strlen(name));
    self->name = name;
    self->parent = self;
    table_init(&self->instance_variables);
    table_init(&self->messages);

    return self;
}
