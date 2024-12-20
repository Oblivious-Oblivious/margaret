#include "TablePrimitives.h"

MargValue __PRIM_TABLE_ADD(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  table_add(&AS_TABLE(args[0])->value, AS_STRING(args[1])->value, args[2]);
  return args[0];
}

MargValue __PRIM_TABLE_GET(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  return table_get(&AS_TABLE(args[0])->value, AS_STRING(args[1])->value);
}

MargValue __PRIM_TABLE_REMOVE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  table_remove(&AS_TABLE(args[0])->value, AS_STRING(args[1])->value);
  return args[0];
}

MargValue __PRIM_TABLE_SIZE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  return MARG_INTEGER(table_size(&AS_TABLE(args[0])->value));
}
