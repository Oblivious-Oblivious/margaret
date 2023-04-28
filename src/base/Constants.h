#ifndef __CONSTANTS_H_
#define __CONSTANTS_H_

#include <stdlib.h> /* size_t */

#include "../opcode/MargValue.h"

/**
 * @brief: Defines a vector data structure storing MargValue constants
 * @param items -> A MargValue pointer array
 * @param alloced -> The total capacity of the vector
 * @param size -> The total number of values
 */
typedef struct Constants {
    MargValue *items;
    size_t alloced;
    size_t size;
} Constants;

/**
 * @brief Creates a new empty constants vector
 * @return Constants*
 */
Constants *constants_new(void);

/**
 * @brief Adds a new element in the constants vector
 * @param self -> Current vector
 * @param item -> Item to add
 */
void constants_add(Constants *self, MargValue item);

/**
 * @brief Get the value of a specific vector index
 * @param self -> Current vector
 * @param index -> Index to get the value from
 * @return MargValue
 */
inline MargValue constants_get(Constants *self, size_t index) {
    return self->items[index];
}

/**
 * @brief Get the total number of values inserted
 * @param self -> Current vector
 * @return size_t -> Number of items in the vector
 */
inline size_t constants_size(Constants *self) {
    return self->size;
}

#endif
