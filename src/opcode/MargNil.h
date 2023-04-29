#ifndef __MARG_NIL_H_
#define __MARG_NIL_H_

#include "MargPointer.h"

/**
 * @brief An object representation of MARG_NIL
 * @param _ -> Inherted object properties
 */
typedef struct MargNil {
    MargPointer _;
} MargNil;

/**
 * @brief Constructs a new nil object
 * @return MargNil*
 */
MargNil *marg_nil_new(void);

#endif
