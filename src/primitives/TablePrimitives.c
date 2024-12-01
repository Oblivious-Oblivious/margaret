#include "TablePrimitives.h"

MargValue __PRIM_TABLE_NEW(VM *vm, MargValue self, MargValue args_value) {
  size_t i;
  MargValue table = MARG_TABLE();
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)self;
  for(i = vector_size(args); i > 0; i -= 2) {
    MargValue prim_args = MARG_TENSOR();
    vector_add(AS_TENSOR(prim_args)->value, args[i - 1]);
    vector_add(AS_TENSOR(prim_args)->value, args[i - 2]);
    __PRIM_TABLE_ADD(NULL, table, prim_args);
  }
  return table;
}

MargValue __PRIM_TABLE_ADD(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  marg_table_add(AS_TABLE(self), AS_STRING(args[0])->value, args[1]);
  return self;
}
