#ifndef __MARG_PRIMITIVE_H_
#define __MARG_PRIMITIVE_H_

#include "MargObject.h"

typedef MargValue (*MargPrimitiveFunction)(VM *, MargValue, MargValue);

/**
 * @brief Defines C-implemented primitives
 * @param _ -> Inherited object properties
 *
 * @param function -> C function pointer
 * @param primitive_name -> Name of primitive
 */
typedef struct MargPrimitive {
  MargObject _;

  MargPrimitiveFunction function;
  const char *primitive_name;
} MargPrimitive;

MargPrimitive *marg_primitive_new(
  VM *vm, const char *primitive_name, MargPrimitiveFunction function
);

#endif
