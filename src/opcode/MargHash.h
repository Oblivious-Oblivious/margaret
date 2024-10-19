#ifndef __MARG_HASH_H_
#define __MARG_HASH_H_

#include "MargObject.h"

/**
 * @brief Defines a hash data structure
 * @param _ -> Inherited MargObject properties
 * @param value -> A pointer to the hash table
 */
typedef struct MargHash {
  MargObject _;
  EmeraldsTable value;
} MargHash;

/**
 * @brief Creates a new emprt MargHash
 * @param vm -> A pointer to the current VM
 * @return MargHash*
 */
MargHash *marg_hash_new(VM *vm);

#define _marg_hash_get_table(self) (&(self)->value)

#define marg_hash_add(self, key, value) \
  table_add(_marg_hash_get_table(self), key, value)
#define marg_hash_add_all(self, other) \
  table_add_all(_marg_hash_get_table(self), _marg_hash_get_table(other))
#define marg_hash_get(self, key) table_get(_marg_hash_get_table(self), key)
#define marg_hash_remove(self, key) \
  table_remove(_marg_hash_get_table(self), key)
#define marg_hash_size(self) table_size(_marg_hash_get_table(self))

#endif
