#ifndef __BITSTRING_PRIMITIVES_H_
#define __BITSTRING_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_BITSTRING_NEW(VM *vm, MargValue args_value);
MargValue __PRIM_BITSTRING_ADD(VM *vm, MargValue args_value);
MargValue __PRIM_BITSTRING_SIZE(VM *vm, MargValue args_value);

#endif
