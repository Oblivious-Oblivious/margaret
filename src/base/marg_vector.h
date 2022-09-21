#ifndef __MARG_VECTOR_H_
#define __MARG_VECTOR_H_

#include <stdlib.h>

/**
 * @struct: marg_vector
 * @brief: Defines a vector data structure
 * @param items -> A void pointer array that contains the heterogenous elements of the vector
 * @param alloced -> The total capacity of the vector
 * @param size -> The total number of values
 */
typedef struct marg_vector {
    void **items;
    size_t alloced;
    size_t size;
} marg_vector;

/**
 * @func: marg_vector_new
 * @brief: Initializes a vector data structure
 * @return: The newly created vector
 */
marg_vector *marg_vector_new(void);

/**
 * @func: marg_vector_add
 * @brief: Adds a new element in the vector
 * @param v -> The vector to use
 * @param item -> The item to add
 * @return The modified vector
 */
marg_vector *marg_vector_add(marg_vector *self, void *item);

/**
 * @func: marg_vector_get
 * @brief: Get the value of a specific vector index
 * @param self -> The vector to use
 * @param index -> The index to get the value of
 * @return The value
 */
void *marg_vector_get(marg_vector *self, size_t index);

/**
 * @brief Sets an element on a specific position
 * @param self -> The vector to use
 * @param index -> The index of the element
 * @param item -> The item to replace with
 */
void marg_vector_set(marg_vector *self, size_t index, void *item);

/**
 * @func: marg_vector_size
 * @brief: Get the total number of values inserted in the vector
 * @param self -> The vector to use
 * @return: The number of items in the vector
 */
size_t marg_vector_size(marg_vector *self);

/**
 * @func: marg_vector_free
 * @brief Frees the memory of the vector
 * @param self -> The vector to free
 */
void marg_vector_free(marg_vector *self);

#endif
