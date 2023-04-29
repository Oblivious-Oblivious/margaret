#ifndef __MARG_TRUE_H_
#define __MARG_TRUE_H_

#include "MargPointer.h"

/**
 * @brief An object representation of MARG_TRUE
 * @param _ -> Inherted object properties
 */
typedef struct MargTrue {
    MargPointer _;
} MargTrue;

/**
 * @brief Constructs a new true object
 * @return MargTrue*
 */
MargTrue *marg_true_new(void);

#endif
