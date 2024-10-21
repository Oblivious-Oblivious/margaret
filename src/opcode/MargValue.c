#include "MargValue.h"

#include "MargBitstring.h"
#include "MargTensor.h"

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
  } else if(IS_TENSOR(self)) {
    size_t i;
    char *res          = string_new("[");
    MargTensor *tensor = AS_TENSOR(self);
    size_t size        = marg_tensor_size(tensor);
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        string_addf(&res, "%s, ", marg_value_format(tensor->value[i]));
      }
      string_addf(&res, "%s", marg_value_format(tensor->value[size - 1]));
    }
    string_add(res, "]");
    return res;
  } else if(IS_TUPLE(self)) {
    size_t i;
    char *res        = string_new("%[");
    MargTuple *tuple = AS_TUPLE(self);
    size_t size      = marg_tensor_size(tuple);
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        string_addf(&res, "%s, ", marg_value_format(tuple->value[i]));
      }
      string_addf(&res, "%s", marg_value_format(tuple->value[size - 1]));
    }
    string_add(res, "]");
    return res;
  } else if(IS_TABLE(self)) {
    size_t i;
    char *res       = string_new("%{");
    EmeraldsTable h = AS_TABLE(self)->value;
    size_t capacity = vector_capacity(h.keys);
    if(table_size(&h) > 0) {
      for(i = 0; i < capacity; i++) {
        if(h.states[i] == TABLE_STATE_FILLED) {
          string_addf(
            &res, "%s: %s, ", h.keys[i], marg_value_format(h.values[i])
          );
        }
      }
      string_ignore_last(res, 2);
    }
    string_add(res, "}");
    return res;
  } else if(IS_BITSTRING(self)) {
    size_t i;
    char *res                = string_new("%(");
    MargBitstring *bitstring = AS_BITSTRING(self);
    size_t size              = marg_bitstring_size(bitstring);
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        string_addf(
          &res,
          "%s::%s, ",
          marg_value_format(AS_BITSTRING(self)->bits->value[i]),
          marg_value_format(AS_BITSTRING(self)->sizes->value[i])
        );
      }
      string_addf(
        &res,
        "%s::%s",
        marg_value_format(AS_BITSTRING(self)->bits->value[size - 1]),
        marg_value_format(AS_BITSTRING(self)->sizes->value[size - 1])
      );
    }
    string_add(res, ")");
    return res;
  } else if(IS_METHOD(self)) {
    char *res = string_new("");
    string_addf(
      &res,
      "< %s#%s >",
      AS_METHOD(self)->bound_object->name,
      AS_METHOD(self)->message_name
    );
    return res;
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
