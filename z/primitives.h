#ifndef __PRIMITIVES_H_
#define __PRIMITIVES_H_

#include "instruction.h"
#include "nan_tagging.h"

/* TODO - Create a raise built-in object */
#define raise(msg) (primitive_RAISE(vm, MARG_STRING(msg), NULL))

static void define_primitive(
  VM *vm, const char *name, const char *object_name, MargPrimitiveFunction msg
) {
  MargObject *obj = NULL;
  if(object_name && object_name[0] == '$') {
    obj = AS_OBJECT(table_get(&vm->global_variables, object_name));
  } else if(object_name && object_name[0] == '@') {
    obj = AS_OBJECT(
      table_get(&vm->current->bound_object->instance_variables, object_name)
    );
  } else {
    obj = AS_OBJECT(table_get(&vm->current->local_variables, object_name));
  }
  table_add(&obj->primitives, name, MARG_PRIMITIVE(vm, msg));
}

static MargValue primitive_RAISE(VM *vm, MargValue self, MargValue *args) {
  (void)vm;
  (void)args;
  fprintf(stdout, "raise: `%s`\n", AS_STRING(self)->value);
  return self;
}

static MargValue primitive_ADD(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(K(-2)) && IS_NUMBER(K(-1))) {
    return MARG_NUMBER(AS_NUMBER(self)->value + AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot add non-number values.");
  }
}

static MargValue primitive_SUB(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(K(-2)) && IS_NUMBER(K(-1))) {
    return MARG_NUMBER(AS_NUMBER(self)->value - AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot subtract non-number values.");
  }
}

static MargValue primitive_MUL(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(K(-2)) && IS_NUMBER(K(-1))) {
    return MARG_NUMBER(AS_NUMBER(self)->value * AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot multiply non-number values.");
  }
}

static MargValue primitive_DIV(VM *vm, MargValue self, MargValue *args) {
  if(IS_NUMBER(K(-1)) && AS_NUMBER(K(-1))->value == 0.0) {
    return raise("Runtime Error: Division by zero");
  } else if(IS_NUMBER(K(-2)) && IS_NUMBER(K(-1))) {
    return MARG_NUMBER(AS_NUMBER(self)->value / AS_NUMBER(args[0])->value);
  } else {
    return raise("TypeError: cannot divide non-number values.");
  }
}

static MargValue primitive_PRINT(VM *vm, MargValue self, MargValue *args) {
  (void)vm;
  (void)args;
  if(RA == 0) {
    printf("ZERO ??\n");
  } else if(IS_NIL(RA)) {
    printf("R%zu = nil\n", GET_INDEX(A));
  } else if(IS_FALSE(RA)) {
    printf("R%zu = false\n", GET_INDEX(A));
  } else if(IS_TRUE(RA)) {
    printf("R%zu = true\n", GET_INDEX(A));
  } else if(IS_NUMBER(RA)) {
    printf("R%zu = %g\n", GET_INDEX(A), AS_NUMBER(RA)->value);
  } else if(IS_STRING(RA)) {
    printf("R%zu = \"%s\"\n", GET_INDEX(A), AS_STRING(RA)->value);
  } else {
    printf("R%zu = UNKNOWN\n", GET_INDEX(A));
  }
  return self;
}

#endif
