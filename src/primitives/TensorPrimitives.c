#include "TensorPrimitives.h"

MargValue __PRIM_TENSOR_NEW(VM *vm, MargValue self, MargValue args_value) {
  size_t i;
  MargValue tensor = MARG_TENSOR();
  MargValue *args  = AS_TENSOR(args_value)->value;
  (void)self;

  for(i = vector_size(args); i > 0; i--) {
    vector_add(AS_TENSOR(tensor)->value, args[i - 1]);
  }

  return tensor;
}

MargValue __PRIM_TENSOR_ADD(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  vector_add(AS_TENSOR(self)->value, args[0]);
  return self;
}

MargValue
__PRIM_TENSOR_ADD_TENSOR(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  vector_add_vector(AS_TENSOR(self)->value, AS_TENSOR(args[0])->value);
  return self;
}

MargValue __PRIM_TENSOR_REMOVE(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  vector_remove(AS_TENSOR(self)->value, AS_INTEGER(args[0])->value);
  return self;
}

MargValue
__PRIM_TENSOR_REMOVE_LAST(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)args_value;
  vector_remove_last(AS_TENSOR(self)->value);
  return self;
}

MargValue __PRIM_TENSOR_LAST(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)args_value;
  return vector_last(AS_TENSOR(self)->value);
}

MargValue __PRIM_TENSOR_SIZE(VM *vm, MargValue self, MargValue args_value) {
  (void)args_value;
  return MARG_INTEGER(vector_size(AS_TENSOR(self)->value));
}
