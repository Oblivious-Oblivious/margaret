#ifndef __MARG_FALSE_H_
#define __MARG_FALSE_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_FALSE
 * @param _ -> Inherted object properties
 */
typedef struct MargFalse {
    MargObject _;
} MargFalse;

/**
 * @brief Constructs a new false object
 * @param vm -> A pointer to the current VM
 * @return MargFalse*
 */
MargFalse *marg_false_new(VM *vm);

#endif
