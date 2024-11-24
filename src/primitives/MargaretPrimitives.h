#ifndef __MARGARET_PRIMITIVES_H_
#define __MARGARET_PRIMITIVES_H_

#include "../opcode/instruction.h"

#include <float.h> /* LDBL_DIG */

/* TODO - Create a raise built-in object */
#define raise(msg) (primitive_RAISE(vm, MARG_STRING(msg), NULL))
p_inline MargValue primitive_RAISE(VM *vm, MargValue self, MargValue *args) {
  (void)vm;
  (void)args;
  fprintf(stdout, "raise: `%s`\n", AS_STRING(self)->value);
  return self;
}

p_inline MargValue primitive_INSPECT(VM *vm, MargValue self, MargValue *args) {
  (void)vm;
  (void)args;

  if(IS_UNDEFINED(self)) {
    printf("<unbound>\n");
  } else if(IS_NIL(self)) {
    printf("$nil\n");
  } else if(IS_FALSE(self)) {
    printf("$false\n");
  } else if(IS_TRUE(self)) {
    printf("$true\n");
  } else if(IS_INTEGER(self)) {
    printf("%td\n", AS_INTEGER(self)->value);
  } else if(IS_FLOAT(self)) {
    printf("%.*g\n", LDBL_DIG, AS_FLOAT(self)->value);
  } else if(IS_LABEL(self)) {
    printf("<%s#%zu>\n", AS_LABEL(self)->name, AS_LABEL(self)->value);
  } else if(IS_SYMBOL(self)) {
    printf("%s\n", AS_SYMBOL(self)->value);
  } else if(IS_STRING(self)) {
    printf("\"%s\"\n", AS_STRING(self)->value);
  } else if(IS_TENSOR(self)) {
    size_t i;
    MargTensor *tensor = AS_TENSOR(self);
    size_t size        = marg_tensor_size(tensor);
    printf("[");
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        printf("%s, ", marg_value_format(tensor->value[i]));
      }
      printf("%s", marg_value_format(tensor->value[size - 1]));
    }
    printf("]\n");
  } else if(IS_TUPLE(self)) {
    size_t i;
    MargTuple *tuple = AS_TUPLE(self);
    size_t size      = marg_tensor_size(tuple);
    printf("%%[");
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        printf("%s, ", marg_value_format(tuple->value[i]));
      }
      printf("%s", marg_value_format(tuple->value[size - 1]));
    }
    printf("]\n");
  } else if(IS_TABLE(self)) {
    size_t i;
    EmeraldsTable h = AS_TABLE(self)->value;
    size_t capacity = vector_capacity(h.keys);
    printf("%%{");
    if(table_size(&h) > 0) {
      for(i = 0; i < capacity; i++) {
        if(h.states[i] == TABLE_STATE_FILLED) {
          printf("%s: %s, ", h.keys[i], marg_value_format(h.values[i]));
        }
      }
    }
    printf("}\n");
  } else if(IS_BITSTRING(self)) {
    size_t i;
    MargBitstring *bitstring = AS_BITSTRING(self);
    size_t size              = marg_bitstring_size(bitstring);
    printf("%%(");
    if(size > 0) {
      for(i = 0; i < size - 1; i++) {
        printf(
          "%s::%s, ",
          marg_value_format(AS_BITSTRING(self)->bits->value[i]),
          marg_value_format(AS_BITSTRING(self)->sizes->value[i])
        );
      }
      printf(
        "%s::%s",
        marg_value_format(AS_BITSTRING(self)->bits->value[size - 1]),
        marg_value_format(AS_BITSTRING(self)->sizes->value[size - 1])
      );
    }
    printf(
      "%s::%s",
      marg_value_format(AS_BITSTRING(self)->bits->value[size - 1]),
      marg_value_format(AS_BITSTRING(self)->sizes->value[size - 1])
    );
    printf(")\n");
  } else if(IS_METHOD(self)) {
    if(AS_METHOD(self)->message_name[0] == '\0') {
      printf("< proc#%zx >\n", self);
    } else {
      printf(
        "< %s#%s >\n",
        AS_METHOD(self)->bound_object->name,
        AS_METHOD(self)->message_name
      );
    }
  } else if(IS_PRIMITIVE(self)) {
    printf("< PRIM#%s >\n", AS_PRIMITIVE(self)->primitive_name);
  } else {
    printf("to_string on object with proto: %s\n", AS_OBJECT(self)->name);
  }
  return self;
}

#endif
