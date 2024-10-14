#ifndef __MARG_FLOAT_H_
#define __MARG_FLOAT_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_FLOAT
 * @param _ -> Inherted object properties
 * @param value -> Actual double value of Float object
 */
typedef struct MargFloat {
  MargObject _;
  double value;
} MargFloat;

/**
 * @brief Constructs a new float object
 * @param vm -> A pointer to the current VM
 * @param value -> Actual C double value
 * @return MargFloat*
 */
MargFloat *marg_float_new(VM *vm, double value);

#endif
