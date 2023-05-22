#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint64_t */

#include "MargObject.h"

/**
 * @brief Defines a string representation for Margaret
 * @param _ -> Inherited object properties
 * @param size -> Number of characters
 * @param chars -> Actual character array
 */
typedef struct MargString {
    MargObject _;
    size_t size;
    uint64_t hash;
    char chars[];
} MargString;

/**
 * @brief Creates a string without dependencies on MargObject
 * 
 * @param vm 
 * @param chars 
 * @return MargValue 
 */
MargValue orphan_marg_string_new(VM *vm, char *chars);

/**
 * @brief Creates a new MargString as an object
 * @param vm -> Current VM
 * @param chars -> Initial characters
 * @return MargString* -> Newly created string
 */
MargString *marg_string_new(VM *vm, char *chars);

#endif
