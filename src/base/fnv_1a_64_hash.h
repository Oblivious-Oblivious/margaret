#ifndef __FNV_1A_64_HASH_H_
#define __FNV_1A_64_HASH_H_

#include <stdint.h> /* uint64_t */
#include <stdlib.h> /* size_t */

/**
 * @brief Implementation of the fnv reverse (xor first, mult later)
 * @param key
 * @param size
 * @return uint64_t hash
 */
uint64_t fnv_1a_64_hash(char *key, size_t size);

#endif
