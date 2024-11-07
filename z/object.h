#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "vm.h"

typedef struct Object {
  bool is_marked;
  struct Object *next;
  VM *bound_vm;

  char *name;
  Value parent;
  Value instance_registers[MAX_REGISTERS];
  EmeraldsTable instance_variables;
  EmeraldsTable messages;
} Object;

typedef struct Nil {
  Object _;
} Nil;

typedef struct False {
  Object _;
} False;

typedef struct True {
  Object _;
} True;

typedef struct Number {
  Object _;

  double value;
} Number;

typedef struct String {
  Object _;
  char *value;
} String;

typedef struct Method {
  Object _;

  Object *bound_object;
  struct Method *bound_method;

  char *message_name;

  char **arguments;
  Value local_registers[MAX_REGISTERS];
  Value *constants;
  EmeraldsTable local_variables;

  Instruction *bytecode;
  size_t ip;
} Method;

Object *value_object_new(VM *bound_vm, size_t size, Value proto, char *name);
Nil *value_nil_new(VM *vm);
False *value_false_new(VM *vm);
True *value_true_new(VM *vm);
Number *value_number_new(VM *vm, double value);
String *value_string_new(VM *vm, char *chars);
Method *value_method_new(
  VM *vm, Object *bound_object, Method *bound_method, char *message_name
);

#endif
