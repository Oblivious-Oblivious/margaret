#ifndef __MARG_INTEGER_H_
#define __MARG_INTEGER_H_

#include <stdint.h> /* int64_t */

#include "MargObject.h"

/**
 * @brief An object representation of MARG_INTEGER
 * @param _ -> Inherted object properties
 */
typedef struct MargInteger {
    MargObject _;
    int64_t value;
} MargInteger;

/**
 * @brief Constructs a new integer object
 * @param global_variables -> A pointer to the current VM's global variables
 * @param value -> Actual C int value
 * @return MargInteger*
 */
MargInteger *marg_integer_new(table *global_variables, int64_t value);

#endif
