#include "object.h"

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "nan_tagging.h"

Object *
value_object_new(VM *bound_vm, size_t size, Value proto, const char *name) {
  Object *self = (Object *)malloc(sizeof(Object) * size);

  self->is_marked = false;
  self->next      = NULL;
  self->bound_vm  = bound_vm;

  self->name   = name;
  self->parent = proto;

  table_init(&self->instance_variables);
  table_init(&self->messages);

  table_add_all(
    &self->instance_variables, &AS_MARG_OBJECT(self->parent)->instance_variables
  );

  table_add(&self->instance_variables, "@self", QNAN_BOX(self));
  table_add(&self->instance_variables, "@super", self->parent);
  table_add(&bound_vm->global_variables, name, QNAN_BOX(self));

  return self;
}

Number *value_number_new(VM *vm, double value) {
  Object *obj = (Object *)value_object_new(
    vm,
    sizeof(Number),
    table_get(&vm->global_variables, "$Margaret"),
    string_new("$Number")
  );
  Number *self = (Number *)obj;

  self->value = value;

  return self;
}

String *value_string_new(VM *vm, char *chars) {
  size_t size = string_size(chars);
  Object *obj = (Object *)value_object_new(
    vm,
    sizeof(String) + size + 1,
    table_get(&vm->global_variables, "$Margaret"),
    string_new("$String")
  );
  String *self = (String *)obj;

  self->value = chars;

  return self;
}

Method *value_method_new(
  VM *vm, Object *bound_object, Method *bound_method, const char *message_name
) {
  Object *obj = (Object *)value_object_new(
    vm,
    sizeof(Method),
    table_get(&vm->global_variables, "$Margaret"),
    string_new("$Method")
  );
  Method *self = (Method *)obj;

  self->bound_object = bound_object;
  self->bound_method = bound_method;

  self->message_name = message_name;

  self->arguments = NULL;
  self->constants = NULL;
  table_init(&self->local_variables);

  self->bytecode = NULL;
  self->ip       = 0;

  return self;
}
