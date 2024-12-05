#ifndef __PRIMITIVES_H_
#define __PRIMITIVES_H_

#include "BitstringPrimitives.h"
#include "MargaretPrimitives.h"
#include "NumericPrimitives.h"
#include "StringPrimitives.h"
#include "TablePrimitives.h"
#include "TensorPrimitives.h"
#include "TuplePrimitives.h"

void define_primitive(
  VM *vm, const char *name, const char *object_name, MargPrimitiveFunction msg
);

#endif
