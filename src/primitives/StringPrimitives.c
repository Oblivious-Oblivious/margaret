#include "StringPrimitives.h"

MargValue __PRIM_STRING_ADDN(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_addn(
    AS_STRING(self)->value,
    AS_STRING(args[0])->value,
    AS_INTEGER(args[1])->value
  );
  return self;
}

MargValue __PRIM_STRING_ADD(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_add(AS_STRING(self)->value, AS_STRING(args[0])->value);
  return self;
}

MargValue __PRIM_STRING_ADDI(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_addi(AS_STRING(self)->value, AS_STRING(args[0])->value);
  return self;
}

MargValue __PRIM_STRING_SIZE(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)args_value;
  return MARG_INTEGER(string_size(AS_STRING(self)->value));
}

MargValue __PRIM_STRING_SHORTEN(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_shorten(AS_STRING(self)->value, AS_INTEGER(args[0])->value);
  return self;
}

MargValue
__PRIM_STRING_SKIP_FIRST(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_skip_first(AS_STRING(self)->value, AS_INTEGER(args[0])->value);
  return self;
}

MargValue
__PRIM_STRING_IGNORE_LAST(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_ignore_last(AS_STRING(self)->value, AS_INTEGER(args[0])->value);
  return self;
}

MargValue __PRIM_STRING_DELETE(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)args_value;
  string_delete(AS_STRING(self)->value);
  return self;
}

MargValue __PRIM_STRING_REMOVE(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  string_remove(AS_STRING(self)->value, AS_INTEGER(args[0])->value);
  return self;
}

MargValue __PRIM_STRING_EQUALS(VM *vm, MargValue self, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  if(string_equals(AS_STRING(self)->value, AS_STRING(args[0])->value)) {
    return MARG_TRUE;
  } else {
    return MARG_FALSE;
  }
}
