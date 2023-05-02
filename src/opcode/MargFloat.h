#ifndef __MARG_FLOAT_H_
#define __MARG_FLOAT_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_FLOAT
 * @param _ -> Inherted object properties
 */
typedef struct MargFloat {
    MargObject _;
    double value;
} MargFloat;

/**
 * @brief Constructs a new float object
 * @param global_variables -> A pointer to the current VM's global variables
 * @param value -> Actual C double value
 * @return MargFloat*
 */
MargFloat *marg_float_new(table *global_variables, double value);

#endif
