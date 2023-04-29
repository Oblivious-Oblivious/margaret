#ifndef __MARG_FALSE_H_
#define __MARG_FALSE_H_

#include "MargPointer.h"

/**
 * @brief An object representation of MARG_FALSE
 * @param _ -> Inherted object properties
 */
typedef struct MargFalse {
    MargPointer _;
} MargFalse;

/**
 * @brief Constructs a new false object
 * @return MargFalse*
 */
MargFalse *marg_false_new(void);

#endif
