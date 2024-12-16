#include "BitstringPrimitives.h"

MargValue __PRIM_BITSTRING_NEW(VM *vm, MargValue args_value) {
  size_t i;
  MargValue bitstring = MARG_BITSTRING();
  MargValue *args     = AS_TENSOR(args_value)->value;

  for(i = 0; i < vector_size(args); i += 2) {
    vector_add(AS_BITSTRING(bitstring)->bits->value, args[i]);
    vector_add(AS_BITSTRING(bitstring)->sizes->value, args[i + 1]);
  }

  return bitstring;
}

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
