#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

// TODO docs comment all function definitions and structs

#include <stdlib.h> /* size_t */
#include "../base/boolean.h"
#include "../base/table.h"

typedef struct MargMethod MargMethod;
typedef struct MargProc MargProc;

/**
 * @brief A representation of user-defined object
 * @param is_marked -> Flag signaling if the object is marked for garbage collection
 * @param next -> Turns the struct into a linked list of objects
 * @param name -> Name of the object
 * @param instance_variables -> Object scoped @variables
 * @param messages -> A table for messages pointing to a vector of methods
 * @param bound_vm -> A pointer to the current VM
 */
typedef struct MargObject {
    bool is_marked;
    struct MargObject *next;

    VM *bound_vm;

    char *name;
    table instance_variables;
    table messages;
} MargObject;

/**
 * @brief Creates a new object instance
 * @param size -> Size of the pointer
 * @param name -> Name of the object
 * @return MargObject*
 */
MargObject *marg_object_new(VM *bound_vm, size_t size, char *name);

#endif
