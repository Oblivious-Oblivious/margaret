#include "BitstringPrimitives.h"

MargValue __PRIM_BITSTRING_NEW(VM *vm, MargValue self, MargValue args_value) {
  size_t i;
  MargValue bitstring = MARG_BITSTRING();
  MargValue *args     = AS_TENSOR(args_value)->value;
  (void)self;
  for(i = vector_size(args); i > 0; i -= 2) {
    MargValue prim_args = MARG_TENSOR();
    vector_add(AS_TENSOR(prim_args)->value, args[i - 1]);
    vector_add(AS_TENSOR(prim_args)->value, args[i - 2]);
    __PRIM_BITSTRING_ADD(NULL, bitstring, prim_args);
  }
  return bitstring;
}

MargValue __PRIM_BITSTRING_ADD(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  vector_add(AS_BITSTRING(self)->bits->value, args[0]);
  vector_add(AS_BITSTRING(self)->sizes->value, args[1]);
  return self;
}

MargValue __PRIM_BITSTRING_SIZE(VM *vm, MargValue self, MargValue args_value) {
  (void)args_value;
  return MARG_INTEGER(vector_size(AS_BITSTRING(self)->bits->value));
}
