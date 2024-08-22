#include "MargObject.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "MargValue.h"

MargObject *marg_object_new(VM *bound_vm, size_t size, char *name) {
  MargObject *self = (MargObject *)malloc(sizeof(MargObject) * size);

  self->is_marked = false;
  self->next      = NULL;

  self->bound_vm = bound_vm;

  self->name   = (char *)malloc(sizeof(char) * string_size(name));
  self->name   = name;
  self->parent = self;
  table_init(&self->instance_variables);
  table_init(&self->messages);

  return self;
}

char *marg_object_to_string_with_hash(MargValue object) {
  char *res         = string_new("");
  char *object_name = AS_OBJECT(object)->name;
  string_addf(
    &res,
    "%s@%s",
    object_name,
    // TODO - Add hash
    "somehash"
  );
  return res;
}
