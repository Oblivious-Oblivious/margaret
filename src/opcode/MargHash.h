#ifndef __MARG_HASH_H_
#define __MARG_HASH_H_

#include <stdlib.h> /* size_t */

#include "MargObject.h"
#include "MargValue.h"

// TODO Implement data-oriented approach by separating keys with values
//      for better memory compaction, and less cache misses
// MargHashKeys -> hash -> {key1: index1, key2: index2, ...}
// MargHashValues -> vector -> [index1, index2, ...]

/**
 * @brief Defines a container for a key/value pair
 * @param key
 * @param value
 */
typedef struct MargHashEntry {
    MargValue key;
    MargValue value;
} MargHashEntry;

/**
 * @brief Defines a hash data structure
 * @param _ -> Inherited MargObject properties
 * @param alloced -> Total capacity of the hash
 * @param size -> Total number of entries
 * @param entires -> A MargHashEntry pointer array
 */
typedef struct MargHash {
    MargObject _;

    size_t alloced;
    size_t size;
    MargHashEntry *entries;
} MargHash;

/**
 * @brief Creates a new emprt MargHash
 * @param vm -> A pointer to the current VM
 * @return MargHash*
 */
MargHash *marg_hash_new(VM *vm);

/**
 * @brief Inserts given key/value pair into the MargHash
        Overrites value if the key exists
 * @param self -> Current MargHash
 * @param key
 * @param value
 */
void marg_hash_add(MargHash *self, MargValue key, MargValue value);

/**
 * @brief Retrieves the value of the corresponding key,
    and saves it into the passed pointer parameter
 * @param self -> Current MargHash
 * @param key -> Key of value we are searching for
 * @return -> Result pointer
 */
MargValue marg_hash_get(MargHash *self, MargValue key);

/**
 * @brief Deletes the value of the corresponding key
 * @param self -> Current MargHash
 * @param key -> Key of value we are deleting
 */
void marg_hash_delete(MargHash *self, MargValue key);

/**
 * @brief Get the number of entries inserted
 * @param self -> Current MargHash
 * @return size_t -> Number of entries
 */
#define marg_hash_size(self) \
    (self)->size;

/**
 * @brief String representation for hash literals in the Java style
 * @param object -> The hash object as a MargValue
 * @return char*
 */
char *marg_hash_to_string(MargValue object);

#endif
