#ifndef __MARGARET_PRIMITIVES_H_
#define __MARGARET_PRIMITIVES_H_

#include "../opcode/instruction.h"

#include <float.h> /* LDBL_DIG */

/* TODO - Create a raise built-in object */
#define raise(msg) (primitive_RAISE(vm, MARG_STRING(msg), MARG_UNDEFINED))
MargValue primitive_RAISE(VM *vm, MargValue self, MargValue args_value);
/* MargValue primitive_DNU(VM *vm, MargValue self, MargValue args_value); */
/* MargValue primitive_CLONE(VM *vm, MargValue self, MargValue args_value); */
MargValue __PRIM_INSPECT(VM *vm, MargValue self, MargValue args_value);

#endif
