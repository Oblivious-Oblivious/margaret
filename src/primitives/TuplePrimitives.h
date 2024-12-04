#ifndef __TUPLE_PRIMITIVES_H_
#define __TUPLE_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_TUPLE_NEW(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_TUPLE_ADD(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_TUPLE_SIZE(VM *vm, MargValue self, MargValue args_value);

#endif