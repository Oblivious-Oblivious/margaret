#include "MargValue.h"

#include <float.h> /* LDBL_DIG */

char *marg_value_format(MargValue self) {
  if(IS_UNDEFINED(self)) {
    return string_new("<unbound>");
  } else if(IS_NIL(self)) {
    return string_new("$nil");
  } else if(IS_FALSE(self)) {
    return string_new("$false");
  } else if(IS_TRUE(self)) {
    return string_new("$true");
  } else if(IS_INTEGER(self)) {
    char *res = string_new("");
    string_addf(&res, "%lld", AS_INTEGER(self)->value);
    return res;
  } else if(IS_FLOAT(self)) {
    char *res = string_new("");
    string_addf(&res, "%.*Lg", LDBL_DIG, AS_FLOAT(self)->value);
    return res;
  } else if(IS_LABEL(self)) {
    char *res = string_new("");
    string_addf(&res, "<%s:%zu>", AS_LABEL(self)->value, AS_LABEL(self)->index);
    return res;
  } else if(IS_SYMBOL(self)) {
    char *res = string_new("");
    string_addf(&res, "%s", AS_SYMBOL(self)->value);
    return res;
  } else if(IS_STRING(self)) {
    char *res = string_new("");
    string_addf(&res, "\"%s\"", AS_STRING(self)->value);
    return res;
  } else if(IS_METHOD(self)) {
    char *res = string_new("");
    string_addf(
      &res,
      "< %s#%s >",
      AS_METHOD(self)->bound_object->name,
      AS_METHOD(self)->message_name->value
    );
    return res;
  } else if(IS_TENSOR(self)) {
    return NULL;
  } else if(IS_TUPLE(self)) {
    return NULL;
  } else if(IS_HASH(self)) {
    return NULL;
  } else if(IS_BITSTRING(self)) {
    return NULL;
  } else {
    return string_new(AS_OBJECT(self)->name);
  }
}

/* TODO - Check if needed */
char *marg_value_as_variable(MargValue self) {
  char *res = string_new("");

  if(IS_STRING(self)) {
    string_add(res, AS_STRING(self)->value);
  }

  return res;
}
