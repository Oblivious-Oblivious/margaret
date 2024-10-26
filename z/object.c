#include "object.h"

#include "../libs/EmeraldsString/export/EmeraldsString.h"

Object *value_object_new(VM *bound_vm, size_t size, Type type) {
  Object *self = (Object *)malloc(sizeof(Object) * size);

  self->is_marked = false;
  self->type      = type;
  self->next      = NULL;
  self->bound_vm  = bound_vm;

  return self;
}

Nil *value_nil_new(VM *vm) {
  Object *obj = (Object *)value_object_new(vm, sizeof(Nil), TYPE_MARG_NIL);
  Nil *self   = (Nil *)obj;

  return self;
}

False *value_false_new(VM *vm) {
  Object *obj = (Object *)value_object_new(vm, sizeof(False), TYPE_MARG_FALSE);
  False *self = (False *)obj;

  return self;
}

True *value_true_new(VM *vm) {
  Object *obj = (Object *)value_object_new(vm, sizeof(True), TYPE_MARG_TRUE);
  True *self  = (True *)obj;

  return self;
}

Number *value_number_new(VM *vm, double value) {
  Object *obj =
    (Object *)value_object_new(vm, sizeof(Number), TYPE_MARG_NUMBER);
  Number *self = (Number *)obj;

  self->value = value;

  return self;
}

String *value_string_new(VM *vm, char *chars) {
  size_t size = string_size(chars);
  Object *obj =
    (Object *)value_object_new(vm, sizeof(String) + size + 1, TYPE_MARG_STRING);
  String *self = (String *)obj;

  self->value = chars;

  return self;
}
