#include "MargObject.h"

#include "../base/memory.h"

MargObject *marg_object_new(VM *bound_vm, size_t size, char *name, size_t name_size) {
    MargObject *self = (MargObject*)collected_malloc(sizeof(MargObject) * size);

    self->is_marked = false;
    self->next = NULL;

    self->name = (char*)malloc(sizeof(char) * name_size);
    self->name = name;
    table_init(&self->instance_variables);
    table_init(&self->messages);

    self->bound_vm = bound_vm;

    return self;
}
