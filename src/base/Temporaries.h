#ifndef __TEMPORARIES_H_
#define __TEMPORARIES_H_

#include <stdlib.h> /* size_t */

#include "../opcode/MargValue.h"

/**
 * @brief: Defines a vector data structure storing MargValue temporaries
 * @param items -> A MargValue pointer array
 * @param alloced -> The total capacity of the vector
 * @param size -> The total number of values
 */
typedef struct Temporaries {
    MargValue *items;
    size_t alloced;
    size_t size;
} Temporaries;

/**
 * @brief Creates a new empty temporaries vector
 * @return Temporaries*
 */
Temporaries *temporaries_new(void);

/**
 * @brief Adds a new element in the temporaries vector
 * @param self -> Current vector
 * @param item -> Item to add
 */
void temporaries_add(Temporaries *self, MargValue item);

/**
 * @brief Get the value of a specific vector index
 * @param self -> Current vector
 * @param index -> Index to get the value from
 * @return MargValue
 */
inline MargValue temporaries_get(Temporaries *self, size_t index) {
    return self->items[index];
}

/**
 * @brief Get the total number of values inserted
 * @param self -> Current vector
 * @return size_t -> Number of items in the vector
 */
inline size_t temporaries_size(Temporaries *self) {
    return self->size;
}

#endif
