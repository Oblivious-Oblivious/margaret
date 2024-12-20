#include "TuplePrimitives.h"

MargValue __PRIM_TUPLE_ADD(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  vector_add(AS_TUPLE(args[0])->value, args[1]);
  return args[0];
}

MargValue __PRIM_TUPLE_SIZE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  return MARG_INTEGER(vector_size(AS_TUPLE(args[0])->value));
}
