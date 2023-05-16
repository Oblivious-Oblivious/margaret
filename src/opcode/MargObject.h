#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

#include <stdlib.h> /* size_t */
#include "../base/boolean.h"
#include "../base/table.h"

typedef struct MargObject MargObject;
typedef struct MargMethod MargMethod;
typedef struct MargProc MargProc;
typedef struct VM VM;

/**
 * @brief A representation of user-defined object
 * @param is_marked -> Flag signaling if the object is marked for garbage collection
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
    table instance_variables;
    table messages;
};

/**
 * @brief Creates a new object instance
 * @param size -> Size of the pointer
 * @param name -> Name of the object
 * @return MargObject*
 */
MargObject *marg_object_new(VM *bound_vm, size_t size, char *name);

#endif
