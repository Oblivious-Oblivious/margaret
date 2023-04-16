#ifndef __CHUNK_H_
#define __CHUNK_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint8_t */
#include <stdarg.h> /* va_start, va_end, va_list, va_arg */

#include "../base/memory.h"

typedef struct Chunk {
    uint8_t *bytecode;
    size_t alloced;
    size_t size;
} Chunk;

/**
 * @brief Creates a new empty chunk
 * @return Chunk*
 */
Chunk *chunk_new(void);

/**
 * @func: chunk_add
 * @brief: Adds a new element in the chunk
 * @param v -> The chunk to use
 * @param item -> The item to add
 * @return The modified chunk
 */
Chunk *chunk_add(Chunk *self, uint8_t item);

/**
 * @func: chunk_get
 * @brief: Get the value of a specific chunk index
 * @param self -> The chunk to use
 * @param index -> The index to get the value of
 * @return The value
 */
uint8_t chunk_get(Chunk *self, size_t index);

/**
 * @brief Sets an element on a specific position
 * @param self -> The chunk to use
 * @param index -> The index of the element
 * @param item -> The item to replace with
 */
void chunk_set(Chunk *self, size_t index, uint8_t item);

/**
 * @func: chunk_size
 * @brief: Get the total number of values inserted in the chunk
 * @param self -> The chunk to use
 * @return: The number of items in the chunk
 */
size_t chunk_size(Chunk *self);

#endif
