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
 * @param vm -> A pointer to the current VM
 */
MargNil *marg_nil_new(VM *vm);

#endif
