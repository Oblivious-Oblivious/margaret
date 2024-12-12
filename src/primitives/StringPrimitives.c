#include "StringPrimitives.h"

/* TODO - Typecheck all primitives before casting */

MargValue __PRIM_STRING_ADD(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_add(AS_STRING(args[0])->value, AS_STRING(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_SIZE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  return MARG_INTEGER(string_size(AS_STRING(args[0])->value));
}

MargValue __PRIM_STRING_SHORTEN(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_shorten(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_SKIP_FIRST(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_skip_first(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_IGNORE_LAST(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_ignore_last(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_DELETE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_delete(AS_STRING(args[0])->value);
  return args[0];
}

MargValue __PRIM_STRING_REMOVE(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_remove(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_EQUALS(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  if(string_equals(AS_STRING(args[0])->value, AS_STRING(args[1])->value)) {
    return MARG_TRUE;
  } else {
    return MARG_FALSE;
  }
}
