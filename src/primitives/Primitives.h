#ifndef __PRIMITIVES_H_
#define __PRIMITIVES_H_

#include "MargaretPrimitives.h"
#include "NumericPrimitives.h"

void define_primitive(
  VM *vm, const char *name, const char *object_name, MargPrimitiveFunction msg
);

#endif
