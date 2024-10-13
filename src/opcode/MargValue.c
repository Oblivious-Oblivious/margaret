#include "MargValue.h"

char *marg_value_format(MargValue self) {
  if(IS_UNDEFINED(self)) {
    return string_new("<unbound>");
  } else if(IS_INTEGER(self)) {
    return marg_integer_to_string(AS_INTEGER(self));
  } else if(IS_FLOAT(self)) {
    return marg_float_to_string(AS_FLOAT(self));
  } else if(IS_LABEL(self)) {
    return marg_label_to_string(AS_LABEL(self));
  } else if(IS_SYMBOL(self)) {
    return marg_symbol_to_string(AS_SYMBOL(self));
  } else if(IS_STRING(self)) {
    return marg_string_to_string(AS_STRING(self));
  } else if(IS_METHOD(self)) {
    return marg_method_to_string(AS_METHOD(self));
  } else if(IS_TENSOR(self)) {
    return marg_tensor_to_string(AS_TENSOR(self));
  } else if(IS_HASH(self)) {
    return marg_hash_to_string(AS_HASH(self));
  } else {
    return string_new(AS_OBJECT(self)->name);
  }
}

char *marg_value_as_variable(MargValue self) {
  char *res = string_new("");

  if(IS_STRING(self)) {
    string_add(res, AS_STRING(self)->value);
  }

  return res;
}
