#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "vm.h"

typedef uint8_t Type;

#define TYPE_MARG_NIL    0x00
#define TYPE_MARG_FALSE  0x01
#define TYPE_MARG_TRUE   0x02
#define TYPE_MARG_NUMBER 0x03
#define TYPE_MARG_STRING 0x04

typedef struct Object {
  bool is_marked;
  Type type;
  struct Object *next;
  VM *bound_vm;
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

Object *value_object_new(VM *bound_vm, size_t size, Type type);
Nil *value_nil_new(VM *vm);
False *value_false_new(VM *vm);
True *value_true_new(VM *vm);
Number *value_number_new(VM *vm, double value);
String *value_string_new(VM *vm, char *chars);

#endif
