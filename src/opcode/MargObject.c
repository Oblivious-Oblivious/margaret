#include "instruction.h"

MargObject *
marg_object_new(VM *vm, size_t size, MargValue proto, const char *name) {
  MargObject *self = (MargObject *)malloc(size);

  self->is_marked = false;
  self->next      = NULL;

  self->bound_vm = vm;

  self->name      = name;
  self->name_hash = komihash_hash(name, string_size(name));
  self->proto     = AS_OBJECT(proto);

  self->instance_index = 0;
  table_init(&self->instance_variables);
  table_init(&self->messages);
  table_init(&self->primitives);

  if(!IS_UNDEFINED(proto)) {
    table_add_all_non_labels(
      &self->proto->instance_variables, &self->instance_variables
    );
  }

  table_add(&self->instance_variables, "@self", self->instance_index);
  self->instance_registers[self->instance_index++] = QNAN_BOX(self);
  table_add(&self->instance_variables, "@super", self->instance_index);
  self->instance_registers[self->instance_index++] = QNAN_BOX(self->proto);

  return self;
}

/* TODO - Refactor as a $Margaret message */
char *marg_object_to_string_with_hash(MargValue object) {
  char *res = string_new("");
  string_addf(
    &res,
    "%s@0x%zx",
    AS_OBJECT(object)->name,
    komihash_hash(AS_OBJECT(object), sizeof(MargObject))
  );
  return res;
}
