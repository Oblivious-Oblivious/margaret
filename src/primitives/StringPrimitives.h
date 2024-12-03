#ifndef __STRING_PRIMITIVES_H_
#define __STRING_PRIMITIVES_H_

#include "MargaretPrimitives.h"

MargValue __PRIM_STRING_ADDN(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_ADD(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_ADDI(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_SIZE(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_SHORTEN(VM *vm, MargValue self, MargValue args_value);
MargValue
__PRIM_STRING_SKIP_FIRST(VM *vm, MargValue self, MargValue args_value);
MargValue
__PRIM_STRING_IGNORE_LAST(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_DELETE(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_REMOVE(VM *vm, MargValue self, MargValue args_value);
MargValue __PRIM_STRING_EQUALS(VM *vm, MargValue self, MargValue args_value);

#endif
