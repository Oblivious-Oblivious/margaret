#ifndef __MARG_NIL_H_
#define __MARG_NIL_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_NIL
 * @param _ -> Inherted object properties
 */
typedef struct MargNil {
    MargObject _;
} MargNil;

/**
 * @brief Constructs a new nil object
 * @return MargNil*
 * @param global_variables -> A pointer to the current VM's global variables
 */
MargNil *marg_nil_new(table *global_variables);

#endif
