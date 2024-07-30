#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

typedef struct MargObject MargObject;

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h"
#include "../vm/vm.h"

/**
 * @brief A representation of user-defined object
 * @param is_marked -> Flag signaling if the object is marked for garbage
 * collection
 * @param next -> Turns the struct into a linked list of objects
 * @param bound_vm -> A pointer to the current VM
 * @param name -> Name of the object
 * @param parent -> Pointer to the parent object (Sets up delegation chain)
 * @param instance_variables -> Object scoped @variables
 * @param messages -> A table for messages pointing to a vector of methods
 */
struct MargObject {
  bool is_marked;
  MargObject *next;

  VM *bound_vm;

  char *name;
  MargObject *parent;
  EmeraldsHashtable instance_variables;
  EmeraldsHashtable messages;
};

/**
 * @brief Creates a new object instance
 * @param size -> Size of the pointer
 * @param name -> Name of the object
 * @return MargObject*
 */
MargObject *marg_object_new(VM *bound_vm, size_t size, char *name);

/**
 * @brief String representation for object literals in the Java style
 * @param object -> The `object` object as a MargValue
 * @return char*
 */
char *marg_object_to_string_with_hash(MargValue object);

#endif
