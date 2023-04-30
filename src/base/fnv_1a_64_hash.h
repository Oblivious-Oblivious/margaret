#ifndef __FNV_1A_64_HASH_H_
#define __FNV_1A_64_HASH_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint64_t */

uint64_t fnv_1a_64_hash(char *key, size_t size);

#endif
