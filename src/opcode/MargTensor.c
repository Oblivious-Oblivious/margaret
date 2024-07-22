#include "MargTensor.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "MargValue.h"

MargTensor *marg_tensor_new(VM *vm, size_t initial_alloced) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargTensor), string_new("$TensorClone")
  );
  MargTensor *self = (MargTensor *)obj;

  MargValue proto_object =
    table_get(&vm->global_variables, MARG_STRING("$Tensor"));
  obj->parent = AS_OBJECT(proto_object);

  obj->instance_variables = obj->parent->instance_variables;

  self->alloced = initial_alloced;
  self->size    = 0;
  self->items =
    (MargValue *)collected_malloc(sizeof(MargValue) * self->alloced);

  return self;
}

char *marg_tensor_to_string(MargTensor *object) {
  char *res = string_new("");

  string_add(res, "[");
  size_t tensor_size = marg_tensor_size(object);
  if(tensor_size > 0) {
    for(size_t i = 0; i < tensor_size - 1; i++) {
      string_addf(res, "%s, ", marg_value_format(marg_tensor_get(object, i)));
    }
    string_addf(
      res, "%s]", marg_value_format(marg_tensor_get(object, tensor_size - 1))
    );
  } else {
    string_add(res, "]");
  }

  return res;
}
