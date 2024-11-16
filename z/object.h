#ifndef __OBJECT_H_
#define __OBJECT_H_

#include "vm.h"

typedef MargValue (*MargPrimitiveFunction)(VM *, MargValue, MargValue *);

typedef struct MargObject {
  bool is_marked;
  struct MargObject *next;
  VM *bound_vm;

  const char *name;
  struct MargObject *proto;
  MargValue instance_registers[MAX_REGISTERS];
  uint16_t instance_index;
  EmeraldsTable instance_variables;
  EmeraldsTable messages;
  EmeraldsTable primitives;
} MargObject;

typedef struct MargNil {
  MargObject _;
} MargNil;

typedef struct MargFalse {
  MargObject _;
} MargFalse;

typedef struct MargTrue {
  MargObject _;
} MargTrue;

typedef struct MargNumber {
  MargObject _;

  double value;
} MargNumber;

typedef struct MargString {
  MargObject _;

  char *value;
} MargString;

typedef struct MargMethod {
  MargObject _;

  MargObject *bound_object;
  struct MargMethod *bound_method;

  const char *message_name;

  char **arguments;
  MargValue local_registers[MAX_REGISTERS];
  uint16_t local_index;
  MargValue *constants;
  EmeraldsTable local_variables;

  Instruction *bytecode;
  size_t ip;
} MargMethod;

typedef struct MargPrimitive {
  MargObject _;

  MargPrimitiveFunction function;
} MargPrimitive;

MargObject *
value_object_new(VM *bound_vm, size_t size, MargValue proto, const char *name);
MargNil *value_nil_new(VM *vm);
MargFalse *value_false_new(VM *vm);
MargTrue *value_true_new(VM *vm);
MargNumber *value_number_new(VM *vm, double value);
MargString *value_string_new(VM *vm, char *chars);
MargMethod *value_method_new(
  VM *vm,
  MargObject *bound_object,
  MargMethod *bound_method,
  const char *message_name
);
MargPrimitive *value_primitive_new(VM *vm, MargPrimitiveFunction function);

#endif
