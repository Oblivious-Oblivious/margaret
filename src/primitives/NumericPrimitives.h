#ifndef __NUMERIC_PRIMITIVES_H_
#define __NUMERIC_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_NUMERIC_ADD(VM *vm, MargValue args_value);
MargValue __PRIM_NUMERIC_SUB(VM *vm, MargValue args_value);
MargValue __PRIM_NUMERIC_MUL(VM *vm, MargValue args_value);
MargValue __PRIM_NUMERIC_DIV(VM *vm, MargValue args_value);

#endif
