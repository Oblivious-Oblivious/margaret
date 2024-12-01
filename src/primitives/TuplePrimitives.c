#include "TuplePrimitives.h"

MargValue __PRIM_TUPLE_NEW(VM *vm, MargValue self, MargValue args_value) {
  size_t i;
  MargValue tuple = MARG_TUPLE();
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)self;

  for(i = vector_size(args); i > 0; i--) {
    vector_add(AS_TENSOR(tuple)->value, args[i - 1]);
  }

  return tuple;
}
