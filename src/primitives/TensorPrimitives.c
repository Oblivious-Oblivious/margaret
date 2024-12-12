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
  (void)self;
  vector_add(AS_TENSOR(args[0])->value, args[1]);
  return args[0];
}

MargValue
__PRIM_TENSOR_ADD_TENSOR(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  vector_add_vector(AS_TENSOR(args[0])->value, AS_TENSOR(args[1])->value);
  return args[0];
}

MargValue __PRIM_TENSOR_REMOVE(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  vector_remove(AS_TENSOR(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue
__PRIM_TENSOR_REMOVE_LAST(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)self;
  MargValue *args = AS_TENSOR(args_value)->value;
  vector_remove_last(AS_TENSOR(args[0])->value);
  return args[0];
}

MargValue __PRIM_TENSOR_LAST(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)self;
  MargValue *args = AS_TENSOR(args_value)->value;
  return vector_last(AS_TENSOR(args[0])->value);
}

MargValue __PRIM_TENSOR_SIZE(VM *vm, MargValue self, MargValue args_value) {
  (void)self;
  MargValue *args = AS_TENSOR(args_value)->value;
  return MARG_INTEGER(vector_size(AS_TENSOR(args[0])->value));
}
