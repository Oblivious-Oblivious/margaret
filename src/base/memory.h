#ifndef __MEMORY_H_
#define __MEMORY_H_

#include <stdlib.h> /* size_t */

// TODO Implement a rudimentary GC

// TODO Eventually remove
#define MEMORY_GROW_FACTOR 2
#define MEMORY_GROW_CAPACITY(capacity) \
  ((capacity) < 8 ? 8 : (capacity) * MEMORY_GROW_FACTOR)

/**
 * @brief Interface to a garbage collected allocation
 * @param nbytes -> Size of allocation
 * @return void*
 */
inline void *collected_malloc(size_t nbytes) { return malloc(nbytes); }

/**
 * @brief Interface to a garbage collected reallocation
 * @param old -> The pointer to resize
 * @param new_size -> Size of reallocation
 * @return void*
 */
inline void *collected_realloc(void *old, size_t new_size) {
  return realloc(old, new_size);
}

#endif
