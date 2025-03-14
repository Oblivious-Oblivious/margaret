#ifndef __TENSOR_PRIMITIVES_H_
#define __TENSOR_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_TENSOR_ADD(VM *vm, MargValue args_value);
MargValue __PRIM_TENSOR_ADD_TENSOR(VM *vm, MargValue args_value);
MargValue __PRIM_TENSOR_REMOVE(VM *vm, MargValue args_value);
MargValue __PRIM_TENSOR_REMOVE_LAST(VM *vm, MargValue args_value);
MargValue __PRIM_TENSOR_LAST(VM *vm, MargValue args_value);
MargValue __PRIM_TENSOR_SIZE(VM *vm, MargValue args_value);

#endif
