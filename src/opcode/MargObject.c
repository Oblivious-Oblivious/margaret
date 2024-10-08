#include "MargValue.h"

MargObject *
marg_object_new(VM *bound_vm, size_t size, MargValue proto, char *name) {
  MargObject *self = (MargObject *)malloc(sizeof(MargObject) * size);

  self->is_marked = false;
  self->next      = NULL;

  self->bound_vm = bound_vm;
  self->name     = name;
  self->parent   = proto;
  table_init(&self->instance_variables);
  table_init(&self->messages);

  if(!IS_UNDEFINED(self->parent)) {
    table_add_all(
      &self->instance_variables, &AS_OBJECT(self->parent)->instance_variables
    );
  }

  table_add(&self->instance_variables, "@self", QNAN_BOX(self));
  table_add(&self->instance_variables, "@super", self->parent);
  table_add(&bound_vm->global_variables, name, QNAN_BOX(self));

  return self;
}

char *marg_object_to_string_with_hash(MargValue object) {
  char *res         = string_new("");
  char *object_name = AS_OBJECT(object)->name;
  string_addf(
    &res,
    "%s@%s",
    object_name,
    /* TODO - Add hash */
    "somehash"
  );
  return res;
}
