#ifndef __PRIMITIVES_H_
#define __PRIMITIVES_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "instruction.h"
#include "nan_tagging.h"

/* TODO - Create a raise built-in object */
#define raise(msg) (primitive_RAISE(vm, MARG_STRING(msg), NULL))

static void define_primitive(
  VM *vm, const char *name, const char *object_name, MargPrimitiveFunction msg
) {
  MargObject *obj = NULL;
  if(object_name && object_name[0] == '$') {
    obj = AS_OBJECT(G(object_name));
  } else if(object_name && object_name[0] == '@') {
    obj = AS_OBJECT(I(object_name));
  } else {
    obj = AS_OBJECT(L(object_name));
  }
  table_add(&obj->primitives, name, MARG_PRIMITIVE(name, msg));
}

static MargValue primitive_RAISE(VM *vm, MargValue self, MargValue *args) {
  (void)vm;
  (void)args;
  fprintf(stdout, "raise: `%s`\n", AS_STRING(self)->value);
  return self;
}

static MargValue primitive_ADD(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(self) && IS_NUMBER(args[0])) {
    return MARG_NUMBER(AS_NUMBER(self)->value + AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot add non-number values.");
  }
}

static MargValue primitive_SUB(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(self) && IS_NUMBER(args[0])) {
    return MARG_NUMBER(AS_NUMBER(self)->value - AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot subtract non-number values.");
  }
}

static MargValue primitive_MUL(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(self) && IS_NUMBER(args[0])) {
    return MARG_NUMBER(AS_NUMBER(self)->value * AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot multiply non-number values.");
  }
}

static MargValue primitive_DIV(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(args[0]) && AS_NUMBER(args[0])->value == 0.0) {
    return raise("Runtime Error: Division by zero");
  } else if(IS_NUMBER(self) && IS_NUMBER(args[0])) {
    return MARG_NUMBER(AS_NUMBER(self)->value / AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot divide non-number values.");
  }
}

static MargValue primitive_INSPECT(VM *vm, MargValue self, MargValue *args) {
  (void)vm;
  (void)args;

  if(self == 0) {
    printf("ZERO ??\n");
  } else if(IS_UNDEFINED(self)) {
    printf("<unbound>\n");
  } else if(IS_NIL(self)) {
    printf("$nil\n");
  } else if(IS_FALSE(self)) {
    printf("$false\n");
  } else if(IS_TRUE(self)) {
    printf("$true\n");
  } else if(IS_NUMBER(self)) {
    printf("%g\n", AS_NUMBER(self)->value);
  } else if(IS_STRING(self)) {
    printf("\"%s\"\n", AS_STRING(self)->value);
  } else if(IS_LABEL(self)) {
    printf("< %s#%zu >\n", AS_LABEL(self)->name, AS_LABEL(self)->value);
  } else if(IS_METHOD(self)) {
    if(AS_METHOD(self)->message_name[0] == '\0') {
      printf("< Proc#%zx >\n", self);
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
