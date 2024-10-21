#ifndef __MARG_BITSTRING_H_
#define __MARG_BITSTRING_H_

#include "MargObject.h"
#include "MargTensor.h"

/**
 * @brief Defines a bitstring representation for Margaret
 * @param _ -> Inherited object properties
 */
typedef struct MargBitstring {
  MargObject _;
  MargTensor *bits;
  MargTensor *sizes;
} MargBitstring;

/**
 * @brief Creates a new bitstring
 * @param vm -> A pointer to the current VM
 * @param initial_size -> User chooses starting length
 * @return MargBitstring*
 */
MargBitstring *marg_bitstring_new(VM *vm);

/**
 * @brief Adds a new element in the MargBitstring
 * @param self -> Current bitstring
 * @param bit -> Bit part
 * @param size -> Bit size part
 */
void marg_bitstring_add(MargBitstring *self, MargValue bit, MargValue size);

/**
 * @brief Get the number of elements inserted
 * @param self -> Current bitstring
 * @return size_t -> Number of elements
 */
size_t marg_bitstring_size(MargBitstring *self);

#endif
