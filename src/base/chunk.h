#ifndef __CHUNK_H_
#define __CHUNK_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint8_t */

#include "memory.h"
#include "temporaries.h"
#include "../opcode/MargValue.h"

#define CHUNK_GROW_FACTOR 1.618

/**
 * @brief: Defines a vector data structure
 * @param items -> A 8-bit integer array for storing opcodes and stack indices
 * @param alloced -> The total memory capacity of the vector
 * @param size -> The total number of values
 * @param lines -> An array which indices map with those of `items`, storing line information for each opcode
 * @param temporaries -> A vector storing actual MargValues of created temporaries
 */
typedef struct chunk {
    uint8_t *items;
    size_t alloced;
    size_t size;

    size_t *lines;
    temporaries *temp_vector;
} chunk;

/**
 * @brief Creates a new empty chunk
 * @return chunk*
 */
chunk *chunk_new(void);

/**
 * @desc: Ensure there is enough space for values in the chunk
 * @param self -> The vector to use
 **/
#define chunk_ensure_space(self) do { \
    size_t new_capacity = (self)->alloced * CHUNK_GROW_FACTOR; \
    uint8_t *new_items = (uint8_t*)collected_realloc((self)->items, sizeof(uint8_t) * new_capacity); \
    size_t *new_lines = (size_t*)collected_realloc((self)->lines, sizeof(size_t) * new_capacity); \
    \
    if(new_items) { \
        (self)->alloced = new_capacity; \
        (self)->items = new_items; \
    } \
    if(new_lines) \
        (self)->lines = new_lines; \
} while(0)

/**
 * @brief Adds a new item in the vector,
        and a new line in the line array
 * @param self -> Current chunk
 * @param item -> Item to add
 * @param line -> Line number the bytecode was emitted from
 */
#define chunk_add(self, item, line) do { \
    if((self)->alloced == (self)->size) \
        chunk_ensure_space((self)); \
    \
    (self)->items[(self)->size] = (item); \
    (self)->lines[(self)->size] = (line); \
    (self)->size++; \
} while(0)

/**
 * @brief Get the value of a specific chunk index
 * @param self -> Current chunk
 * @param index -> Index to get the value from
 * @return uint8_t
 */
#define chunk_get(self, index) (self)->items[(index)]

/**
 * @brief Get the total number of values inserted
 * @param self -> Current chunk
 * @return size_t -> Number of items in the vector
 */
#define chunk_size(self) (self)->size

/**
 * @brief Helper for adding a temporary
    inside the value vector of a chunk
 * @param chunk -> Current chunk
 * @param value -> MargValue
 * @return size_t -> The index the temporary was appended to
 */
#define chunk_temporary_add(chunk, value, index) do { \
    temporaries_add((chunk)->temp_vector, (value)); \
    *(index) = temporaries_size((chunk)->temp_vector) - 1; \
} while(0)

/**
 * @brief Helper for retrieving a temporary from the
    value vector of a chunk using index
 * @param chunk -> Current chunk
 * @param index -> Index of the temporary
 * @return MargValue -> The value of the temporary
 */
#define chunk_temporary_get(chunk, index) \
    temporaries_get((chunk)->temp_vector, (index))

#endif
