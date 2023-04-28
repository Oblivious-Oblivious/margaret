#ifndef __MARG_FLOAT_H_
#define __MARG_FLOAT_H_

#include "MargValue.h"

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
 * @return MargFloat*
 */
MargFloat *marg_float_new(double value);

#endif