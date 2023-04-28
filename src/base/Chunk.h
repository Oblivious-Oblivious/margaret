#ifndef __CHUNK_H_
#define __CHUNK_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint8_t */

#include "Constants.h"
#include "../opcode/MargValue.h"

/**
 * @brief: Defines a vector data structure
 * @param items -> A 8-bit integer array for storing opcodes and stack indices
 * @param alloced -> The total memory capacity of the vector
 * @param size -> The total number of values
 * @param lines -> An array which indices map with those of `items`, storing line information for each opcode
 * @param constants -> A vector storing actual MargValues of created constants
 */
typedef struct Chunk {
    uint8_t *items;
    size_t alloced;
    size_t size;

    size_t *lines;
    Constants *constants;
} Chunk;

/**
 * @brief Creates a new empty chunk
 * @return Chunk*
 */
Chunk *chunk_new(void);

/**
 * @brief Adds a new item in the vector,
        and a new line in the line array
 * @param self -> Current chunk
 * @param item -> Item to add
 * @param line -> Line number the bytecode was emitted from
 */
void chunk_add(Chunk *self, uint8_t item, size_t line);

/**
 * @brief Get the value of a specific chunk index
 * @param self -> Current chunk
 * @param index -> Index to get the value from
 * @return uint8_t
 */
inline uint8_t chunk_get(Chunk *self, size_t index) {
    return self->items[index];
}

/**
 * @brief Get the total number of values inserted
 * @param self -> Current chunk
 * @return size_t -> Number of items in the vector
 */
inline size_t chunk_size(Chunk *self) {
    return self->size;
}

/**
 * @brief Helper for adding a constant
    inside the value vector of a chunk
 * @param chunk -> Current chunk
 * @param value -> MargValue
 * @return size_t -> The index the constant was appended to
 */
uint32_t chunk_constant_add(Chunk *chunk, MargValue value);

/**
 * @brief Helper for retrieving a constant from the
    value vector of a chunk using index
 * @param chunk -> Current chunk
 * @param index -> Index of the constant
 * @return MargValue -> The value of the constant
 */
inline MargValue chunk_constant_get(Chunk *chunk, size_t index) {
    return constants_get(chunk->constants, index);
}

#endif
