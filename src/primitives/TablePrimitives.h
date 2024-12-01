#ifndef __TABLE_PRIMITIVES_H_
#define __TABLE_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_TABLE_NEW(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_TABLE_ADD(VM *vm, MargValue self, MargValue args_value);

#endif
