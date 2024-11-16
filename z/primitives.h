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
    obj = AS_OBJECT(G(object_name));
  } else if(object_name && object_name[0] == '@') {
    obj = AS_OBJECT(I(object_name));
  } else {
    obj = AS_OBJECT(L(object_name));
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

static MargValue primitive_PRIM(VM *vm) {
  ptrdiff_t i;
  ptrdiff_t argc  = AS_NUMBER(RB)->value;
  MargValue self  = K(-1 - argc);
  MargValue *args = NULL;
  char *name      = AS_STRING(RA)->value;

  MargValue prim_msg = table_get(&AS_OBJECT(self)->proto->primitives, name);
  if(IS_UNDEFINED(prim_msg)) {
    return raise("Error: cannot send because primitive does not exist.");
  } else {
    for(i = 1; i <= argc; i++) {
      vector_add(args, K(-i));
    }
    return AS_PRIMITIVE(prim_msg)->function(vm, self, args);
  }
}

static MargValue primitive_PRINT(VM *vm, MargValue self, MargValue *args) {
#define get_register_type(v) \
  (IS_CONSTANT((v))   ? "K"  \
   : IS_LOCAL((v))    ? "L"  \
   : IS_INSTANCE((v)) ? "I"  \
   : IS_GLOBAL((v))   ? "G"  \
                      : "R")

  (void)vm;
  (void)args;

  if(RA == 0) {
    printf("ZERO ??\n");
  } else if(IS_UNDEFINED(RA)) {
    printf("%s%zu = UNDEFINED\n", get_register_type(A), GET_INDEX(A));
  } else if(IS_NIL(RA)) {
    printf("%s%zu = nil\n", get_register_type(A), GET_INDEX(A));
  } else if(IS_FALSE(RA)) {
    printf("%s%zu = false\n", get_register_type(A), GET_INDEX(A));
  } else if(IS_TRUE(RA)) {
    printf("%s%zu = true\n", get_register_type(A), GET_INDEX(A));
  } else if(IS_NUMBER(RA)) {
    printf(
      "%s%zu = %g\n", get_register_type(A), GET_INDEX(A), AS_NUMBER(RA)->value
    );
  } else if(IS_STRING(RA)) {
    printf(
      "%s%zu = \"%s\"\n",
      get_register_type(A),
      GET_INDEX(A),
      AS_STRING(RA)->value
    );
  } else {
    printf("%s%zu = UNKNOWN\n", get_register_type(A), GET_INDEX(A));
  }
  return self;
#undef get_register_type
}

static void primitive_SEND(VM *vm) {
  ptrdiff_t i;
  MargValue msg_value;
  EmeraldsTable object_messages;
  ptrdiff_t argc  = AS_NUMBER(RB)->value;
  MargValue self  = K(-1 - argc);
  MargValue *args = NULL;
  char *name      = AS_STRING(RA)->value;

  object_messages = AS_OBJECT(self)->messages;
  msg_value       = table_get(&object_messages, name);
  if(IS_UNDEFINED(msg_value)) {
    raise("Error: cannot send because message does not exist.");
  } else {
    for(i = 1; i <= argc; i++) {
      vector_add(args, K(-i));
    }
    vm->current = AS_METHOD(msg_value);
    for(i = 0; i < argc; i++) {
      vm->current->local_registers[LOCAL(vm->current->arguments[i])] = args[i];
    }
  }
}

#endif
