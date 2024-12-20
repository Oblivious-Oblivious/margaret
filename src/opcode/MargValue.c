#include "MargValue.h"

#include "../primitives/BitstringPrimitives.h"
#include "../primitives/TensorPrimitives.h"
#include "../primitives/TuplePrimitives.h"

#include <float.h> /* LDBL_DIG */

char *marg_value_format(VM *vm, MargValue self) {
  if(IS_UNDEFINED(self)) {
    return string_new("");
  } else if(IS_NIL(self)) {
    return string_new("$nil");
  } else if(IS_FALSE(self)) {
    return string_new("$false");
  } else if(IS_TRUE(self)) {
    return string_new("$true");
  } else if(IS_INTEGER(self)) {
    char *res = string_new("");
    string_addf(&res, "%td", AS_INTEGER(self)->value);
    return res;
  } else if(IS_FLOAT(self)) {
    char *res = string_new("");
    string_addf(&res, "%.*Lg", LDBL_DIG, AS_FLOAT(self)->value);
    return res;
  } else if(IS_LABEL(self)) {
    char *res = string_new("");
    string_addf(&res, "<%s#%zu>", AS_LABEL(self)->name, AS_LABEL(self)->value);
    return res;
  } else if(IS_SYMBOL(self)) {
    char *res = string_new("");
    string_addf(&res, ":%s", AS_SYMBOL(self)->value);
    return res;
  } else if(IS_STRING(self)) {
    char *res = string_new("");
    string_addf(&res, "\"%s\"", AS_STRING(self)->value);
    return res;
  } else if(IS_TENSOR(self)) {
    size_t i;
    char *res          = string_new("[");
    MargTensor *tensor = AS_TENSOR(self);
    size_t size        = vector_size(tensor->value);
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        string_addf(&res, "%s, ", marg_value_format(vm, tensor->value[i]));
      }
      string_addf(&res, "%s", marg_value_format(vm, tensor->value[size - 1]));
    }
    string_add(res, "]");
    return res;
  } else if(IS_TUPLE(self)) {
    size_t i;
    char *res        = string_new("%[");
    MargTuple *tuple = AS_TUPLE(self);
    size_t size      = vector_size(tuple->value);
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        string_addf(&res, "%s, ", marg_value_format(vm, tuple->value[i]));
      }
      string_addf(&res, "%s", marg_value_format(vm, tuple->value[size - 1]));
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
            &res, "%s: %s, ", h.keys[i], marg_value_format(vm, h.values[i])
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
    size_t size              = vector_size(bitstring->sizes->value);
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        string_addf(
          &res,
          "%s::%s, ",
          marg_value_format(vm, bitstring->bits->value[i]),
          marg_value_format(vm, bitstring->sizes->value[i])
        );
      }
      string_addf(
        &res,
        "%s::%s",
        marg_value_format(vm, bitstring->bits->value[size - 1]),
        marg_value_format(vm, bitstring->sizes->value[size - 1])
      );
    }
    string_add(res, ")");
    return res;
  } else if(IS_METHOD(self)) {
    char *res = string_new("");
    if(AS_METHOD(self)->message_name == NULL) {
      string_addf(&res, "< proc#%zx >", self);
    } else {
      string_addf(
        &res,
        "< %s#%s >",
        AS_METHOD(self)->bound_object->name,
        AS_METHOD(self)->message_name
      );
    }
    return res;
  } else if(IS_PRIMITIVE(self)) {
    char *res = string_new("");
    string_addf(&res, "< PRIM#%s >\n", AS_PRIMITIVE(self)->primitive_name);
    return res;
  } else if(IS_VARIABLE(self)) {
    char *res = string_new("");
    string_addf(&res, marg_value_format(vm, AS_VARIABLE(self)->value));
    return res;
  } else {
    return string_new(AS_OBJECT(self)->name);
  }
}
