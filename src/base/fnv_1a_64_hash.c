#include "fnv_1a_64_hash.h"

uint64_t fnv_1a_64_hash(char *key, size_t size) {
    uint64_t hash = 14695981039346656037u;

    for(size_t i = 0; i < size; i++) {
        hash ^= (uint8_t)key[i];
        hash *= 1099511628211;
    }

    return hash;
}
