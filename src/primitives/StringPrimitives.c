#include "StringPrimitives.h"

/* TODO - Typecheck all primitives before casting */

MargValue __PRIM_STRING_ADD(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  string_add(AS_STRING(args[0])->value, AS_STRING(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_SIZE(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)self;
  MargValue *args = AS_TENSOR(args_value)->value;
  return MARG_INTEGER(string_size(AS_STRING(args[0])->value));
}

MargValue __PRIM_STRING_SHORTEN(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  string_shorten(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue
__PRIM_STRING_SKIP_FIRST(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  string_skip_first(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue
__PRIM_STRING_IGNORE_LAST(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  string_ignore_last(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_DELETE(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)self;
  MargValue *args = AS_TENSOR(args_value)->value;
  string_delete(AS_STRING(args[0])->value);
  return args[0];
}

MargValue __PRIM_STRING_REMOVE(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  string_remove(AS_STRING(args[0])->value, AS_INTEGER(args[1])->value);
  return args[0];
}

MargValue __PRIM_STRING_EQUALS(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  (void)self;
  if(string_equals(AS_STRING(args[0])->value, AS_STRING(args[1])->value)) {
    return MARG_TRUE;
  } else {
    return MARG_FALSE;
  }
}
