#include "MargString.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "MargValue.h"

MargString *marg_string_new(VM *vm, char *chars) {
  size_t size     = string_size(chars);
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargString) + size + 1, string_new("$StringClone")
  );
  MargString *self = (MargString *)obj;

  MargValue proto_object = table_get(&vm->global_variables, "$String");
  obj->parent            = AS_OBJECT(proto_object);

  if(!IS_UNDEFINED(proto_object)) {
    obj->instance_variables = obj->parent->instance_variables;
  }

  self->size = size;
  memcpy(self->chars, chars, size);
  self->chars[size] = '\0';

  return self;
}
