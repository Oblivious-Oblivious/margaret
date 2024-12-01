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
