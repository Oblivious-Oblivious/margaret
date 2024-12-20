#include "BitstringPrimitives.h"

MargValue __PRIM_BITSTRING_ADD(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  vector_add(AS_BITSTRING(args[0])->bits->value, args[1]);
  vector_add(AS_BITSTRING(args[0])->sizes->value, args[2]);
  return args[0];
}

MargValue __PRIM_BITSTRING_SIZE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  return MARG_INTEGER(vector_size(AS_BITSTRING(args[0])->bits->value));
}
