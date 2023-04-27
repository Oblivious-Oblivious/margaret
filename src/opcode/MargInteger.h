#ifndef __MARG_INTEGER_H_
#define __MARG_INTEGER_H_

#include "MargValue.h"

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
 * @return MargInteger*
 */
MargInteger *marg_integer_new(int64_t value);

#endif
