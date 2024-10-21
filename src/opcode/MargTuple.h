#ifndef __MARG_TUPLE_H_
#define __MARG_TUPLE_H_

#include "MargObject.h"

/**
 * @brief Defines a tuple representation for Margaret
 * @param _ -> Inherited object properties
 * @param value -> A pointer to the tuple values
 */
typedef struct MargTuple {
  MargObject _;
  MargValue *value;
} MargTuple;

/**
 * @brief Creates a new tuple
 * @param vm -> A pointer to the current VM
 * @param initial_size -> User chooses starting length
 * @return MargTuple*
 */
MargTuple *marg_tuple_new(VM *vm);

#endif
