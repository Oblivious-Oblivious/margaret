#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

#include "../vm/vm.h"
#include "MargValueType.h"

/**
 * @brief A representation of user-defined object
 * @param is_marked -> If true, the object is read for garbage collection
 * @param next -> Turns the struct into a linked list of objects
 *
 * @param bound_vm -> A pointer to the current VM
 *
 * @param name -> Name of the object
 * @param parent -> Pointer to the parent object (Sets up delegation chain)
 * @param instance_variables -> Object scoped @variables
 * @param messages -> A table for messages pointing to a vector of methods
 */
typedef struct MargObject {
  bool is_marked;
  struct MargObject *next;

  VM *bound_vm;

  const char *name;
  size_t name_hash;
  struct MargObject *proto;
  MargValue instance_registers[MAX_REGISTERS];
  uint32_t instance_index;
  EmeraldsTable instance_variables;
  EmeraldsTable messages;
  EmeraldsTable primitives;
} MargObject;

/**
 * @brief Creates a new object instance
 * @param vm -> Current VM
 * @param size -> Size of the pointer
 * @param proto -> Value of the prototype object
 * @param name -> Name of the object
 * @return MargObject*
 */
MargObject *
marg_object_new(VM *vm, size_t size, MargValue proto, const char *name);

/**
 * @brief String representation for object literals in the Java style
 * @param object -> The `object` object as a MargValue
 * @return char*
 */
char *marg_object_to_string_with_hash(MargValue object);

#endif
