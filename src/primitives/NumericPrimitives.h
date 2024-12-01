#ifndef __NUMERIC_PRIMITIVES_H_
#define __NUMERIC_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_ADD(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_SUB(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_MUL(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_DIV(VM *vm, MargValue self, MargValue args_value);

#endif
