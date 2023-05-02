#ifndef __MARG_TRUE_H_
#define __MARG_TRUE_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_TRUE
 * @param _ -> Inherted object properties
 */
typedef struct MargTrue {
    MargObject _;
} MargTrue;

/**
 * @brief Constructs a new true object
 * @param global_variables -> A pointer to the current VM's global variables
 * @return MargTrue*
 */
MargTrue *marg_true_new(table *global_variables);

#endif
