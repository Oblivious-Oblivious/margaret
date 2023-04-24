#ifndef __MARG_HASH_H_
#define __MARG_HASH_H_

#include <stdlib.h> /* size_t */

#include "../base/boolean.h"
#include "MargValue.h"
#include "MargString.h"

// TODO Implement data-oriented approach by separating keys with values
//      for better memory compaction, and less cache misses
// MargHashKeys -> hash -> {key1: index1, key2: index2, ...}
// MargHashValues -> vector -> [index1, index2, ...]
typedef struct MargHashEntry {
    MargString *key;
    MargValue value;
} MargHashEntry;

typedef struct MargHash {
    size_t count;
    size_t capacity;
    MargHashEntry *entries;
} MargHash;

/**
 * @brief Initializes the values of a hash
 * @param self -> Hash that is passed from the stack
 */
void marg_hash_init(MargHash *self);

/**
 * @brief Inserts given key/value pair into the hash
        Overrites value if the key exists
 * @param self -> Current hash
 * @param key
 * @param value 
 * @return true -> Insertion succeeded
 * @return false -> Insertion failed
 */
bool marg_hash_set(MargHash *self, MargString *key, MargValue value);

/**
 * @brief Retrieves the value of the corresponding key,
    and saves it into the passed pointer parameter
 * @param self -> Current hash
 * @param key -> Key of value we are searching for
 * @param value -> Result pointer
 * @return true -> Retrieval succeeded
 * @return false -> Retrieval failed
 */
bool marg_hash_get(MargHash *self, MargString *key, MargValue *value);

/**
 * @brief Deletes the value of the corresponding key
 * @param self -> Current hash
 * @param key -> Key of value we are deleting
 * @return true -> Deletion succeeded
 * @return false -> Deletion failed
 */
bool marg_hash_delete(MargHash *self, MargString *key);

/**
 * @brief Adds all entries from src to dest
 * @param src -> Initial hash
 * @param dest -> New hash
 */
void marg_hash_add_all(MargHash *src, MargHash *dest);

/**
 * @brief Finds a string key efficiently.
        Checks for equal sizes, hash values and
        only then, mem compares each character
 * @param self -> Current Hash
 * @param chars 
 * @param size 
 * @param hash 
 * @return MargString*
 */
MargString *marg_hash_find_string(MargHash *self, char *chars, size_t size, uint64_t hash);

#endif
