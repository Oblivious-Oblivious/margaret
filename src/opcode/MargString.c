#include "MargString.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "MargValue.h"

/**
 * @brief Creates a string without dependencies on MargObject
 * @param vm
 * @param chars
 * @return MargValue
 */
static MargValue orphan_marg_string_new(VM *vm, char *chars) {
  size_t size      = string_size(chars);
  MargString *self = (MargString *)(MargObject *)marg_object_new(
    vm, sizeof(MargString) + size, string_new("")
  );
  self->hash = fnv_1a_64_hash(chars, size);
  return QNAN_BOX(self);
}

MargString *marg_string_new(VM *vm, char *chars) {
  size_t size     = string_size(chars);
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargString) + size + 1, string_new("$StringClone")
  );
  MargString *self = (MargString *)obj;

  MargValue proto_object = table_get(
    &vm->global_variables, orphan_marg_string_new(vm, string_new("$String"))
  );
  obj->parent = AS_OBJECT(proto_object);

  if(!IS_UNDEFINED(proto_object)) {
    obj->instance_variables = obj->parent->instance_variables;
  }

  self->size = size;
  self->hash = fnv_1a_64_hash(chars, size);
  memcpy(self->chars, chars, size);
  self->chars[size] = '\0';

  return self;
}
