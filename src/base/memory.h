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
#define collected_malloc(nbytes) (malloc((nbytes)))

/**
 * @brief Interface to a garbage collected reallocation
 * @param old -> The pointer to resize
 * @param new_size -> Size of reallocation
 * @return void*
 */
#define collected_realloc(old, new_size) (realloc((old), (new_size)))

#endif
