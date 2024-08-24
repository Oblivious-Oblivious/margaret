#include "MargInteger.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "MargValue.h"

MargInteger *marg_integer_new(VM *vm, ptrdiff_t value) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargInteger), string_new("$IntegerClone")
  );
  MargInteger *self = (MargInteger *)obj;

  MargValue proto_object = table_get(&vm->global_variables, "$Integer");
  obj->parent            = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->value = value;

  return self;
}

char *marg_integer_to_string(MargInteger *object) {
  char *res = string_new("");
  string_addf(&res, "%lld", object->value);
  return res;
}
