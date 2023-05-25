#include "MargObject.h"

#include "../base/memory.h"

#include <string.h> /* strlen */

#include "MargString.h"

MargObject *marg_object_new(VM *bound_vm, size_t size, char *name) {
    MargObject *self = (MargObject*)collected_malloc(sizeof(MargObject) * size);

    self->is_marked = false;
    self->next = NULL;

    self->bound_vm = bound_vm;

    self->name = (char*)collected_malloc(sizeof(char) * strlen(name));
    self->name = name;
    self->parent = self;
    table_init(&self->instance_variables);
    table_init(&self->messages);

    return self;
}

char *marg_object_to_string_with_hash(MargValue object) {
    string *res = string_new("");
    char *object_name = AS_OBJECT(object)->name;
    string_addf(res, "%s@%llx", object_name, fnv_1a_64_hash(object_name, strlen(object_name)));
    return string_get(res);
}
