#include "object.h"

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "instruction.h"
#include "nan_tagging.h"

#define table_add_all_non_labels(src, dst)                           \
  do {                                                               \
    size_t i;                                                        \
    for(i = 0; i < vector_capacity((src)->keys); i++) {              \
      if((src)->states[i] == TABLE_STATE_FILLED) {                   \
        if((src)->keys[i] &&                                         \
           !((src)->keys[i][0] == '@' && (src)->keys[i][1] == ':' && \
             (src)->keys[i][2] == ':')) {                            \
          table_add((dst), (src)->keys[i], (src)->values[i]);        \
        }                                                            \
      }                                                              \
    }                                                                \
  } while(0)

MargObject *
value_object_new(VM *vm, size_t size, MargValue proto, const char *name) {
  size_t i;
  MargObject *self = (MargObject *)malloc(sizeof(MargObject) * size);

  self->is_marked = false;
  self->next      = NULL;
  self->bound_vm  = vm;

  self->name  = name;
  self->proto = AS_OBJECT(proto);

  self->instance_index = 0;
  table_init(&self->instance_variables);
  table_init(&self->messages);
  table_init(&self->primitives);
  for(i = 0; i < MAX_REGISTERS; i++) {
    self->instance_registers[i] = MARG_UNDEFINED;
  }

  if(!IS_UNDEFINED(proto)) {
    table_add_all_non_labels(
      &self->proto->instance_variables, &self->instance_variables
    );
  }

  table_add(&self->instance_variables, "@self", 0);
  self->instance_registers[self->instance_index++] = QNAN_BOX(self);
  table_add(&self->instance_variables, "@super", 1);
  self->instance_registers[self->instance_index++] = QNAN_BOX(self->proto);

  return self;
}

MargNumber *value_number_new(VM *vm, double value) {
  MargObject *obj = (MargObject *)value_object_new(
    vm, sizeof(MargNumber), G("$Number"), string_new("")
  );
  MargNumber *self = (MargNumber *)obj;

  self->value = value;

  return self;
}

MargString *value_string_new(VM *vm, char *chars) {
  size_t size     = string_size(chars);
  MargObject *obj = (MargObject *)value_object_new(
    vm, sizeof(MargString) + size + 1, G("$String"), string_new("")
  );
  MargString *self = (MargString *)obj;

  self->value = chars;

  return self;
}

MargLabel *value_label_new(VM *vm) {
  MargObject *obj = (MargObject *)value_object_new(
    vm, sizeof(MargLabel), G("$Label"), string_new("label value")
  );
  MargLabel *self = (MargLabel *)obj;

  self->value = vector_size(vm->current->bytecode);

  return self;
}

MargMethod *value_method_new(
  VM *vm,
  MargObject *bound_object,
  MargMethod *bound_method,
  const char *message_name
) {
  size_t i;
  MargObject *obj = (MargObject *)value_object_new(
    vm, sizeof(MargMethod), G("$Method"), string_new("")
  );
  MargMethod *self = (MargMethod *)obj;

  self->bound_object = bound_object;
  self->bound_method = bound_method;

  self->message_name = message_name;

  self->arguments = NULL;
  self->constants = NULL;
  table_init(&self->local_variables);
  self->local_index = 0;
  for(i = 0; i < MAX_REGISTERS; i++) {
    self->local_registers[i] = MARG_UNDEFINED;
  }

  self->bytecode = NULL;
  self->ip       = -1;

  return self;
}

MargPrimitive *value_primitive_new(VM *vm, MargPrimitiveFunction function) {
  MargObject *obj = (MargObject *)value_object_new(
    vm, sizeof(MargPrimitive), G("Primitive"), string_new("")
  );
  MargPrimitive *self = (MargPrimitive *)obj;

  table_remove(&obj->instance_variables, "@super");
  self->function = function;

  return self;
}
