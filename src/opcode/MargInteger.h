#ifndef __MARG_INTEGER_H_
#define __MARG_INTEGER_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_INTEGER
 * @param _ -> Inherted object properties
 */
typedef struct MargInteger {
  MargObject _;
  ptrdiff_t value;
} MargInteger;

/**
 * @brief Constructs a new integer object
 * @param vm -> A pointer to the current VM
 * @param value -> Actual C int value
 * @return MargInteger*
 */
MargInteger *marg_integer_new(VM *vm, ptrdiff_t value);

#endif
