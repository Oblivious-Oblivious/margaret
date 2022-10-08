#ifndef __MEMORY_H_
#define __MEMORY_H_

#include <stdlib.h> /* size_t */

/**
 * @brief Interface to a garbage collected allocation
 * @param nbytes -> Size of allocation
 * @return void*
 */
void *collected_malloc(size_t nbytes);

/**
 * @brief Interface to a garbage collected reallocation
 * @param old -> The pointer to resize
 * @param new_size -> Size of reallocation
 * @return void* 
 */
void *collected_realloc(void *old, size_t new_size);

#endif
