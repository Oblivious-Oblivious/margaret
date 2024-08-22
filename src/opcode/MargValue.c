#include "MargValue.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */

char *marg_value_format(MargValue self) {
  if(IS_UNDEFINED(self)) {
    return string_new("<unbound>");
  } else if(IS_INTEGER_CLONE(self)) {
    return string_new(marg_integer_to_string(AS_INTEGER(self)));
  } else if(IS_FLOAT_CLONE(self)) {
    return string_new(marg_float_to_string(AS_FLOAT(self)));
  } else if(IS_STRING_CLONE(self)) {
    char *res = string_new("");
    string_addf(&res, "\"%s\"", AS_STRING(self)->chars);
    return res;
  } else if(IS_METHOD_CLONE(self)) {
    return string_new(marg_method_to_string(AS_METHOD(self)));
  } else if(IS_PROC_CLONE(self)) {
    return string_new(marg_proc_to_string(AS_PROC(self)));
  } else if(IS_TENSOR_CLONE(self)) {
    return string_new(marg_tensor_to_string(AS_TENSOR(self)));
  } else if(IS_HASH_CLONE(self)) {
    return string_new(marg_hash_to_string(AS_HASH(self)));
  } else {
    return string_new(AS_OBJECT(self)->name);
  }
}

char *marg_value_as_variable(MargValue self) {
  char *res = string_new("");

  if(IS_STRING_CLONE(self)) {
    string_addf(&res, "%s", AS_STRING(self)->chars);
  }

  return res;
}
