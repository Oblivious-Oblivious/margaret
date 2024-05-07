#ifndef __TEMPORARIES_H_
#define __TEMPORARIES_H_

#include "../opcode/MargValueType.h"
#include "memory.h"

#define TEMPORARIES_GROW_FACTOR 1.618

/**
 * @brief: Defines a vector data structure storing MargValue temporaries
 * @param items -> A MargValue pointer array
 * @param alloced -> The total capacity of the vector
 * @param size -> The total number of values
 */
typedef struct temporaries {
  MargValue *items;
  size_t alloced;
  size_t size;
} temporaries;

/**
 * @brief Creates a new empty temporaries vector
 * @return temporaries*
 */
#define temporaries_init(self)                                            \
  do {                                                                    \
    (self)->alloced = 32;                                                 \
    (self)->size    = 0;                                                  \
    (self)->items =                                                       \
      (MargValue *)collected_malloc(sizeof(MargValue) * (self)->alloced); \
  } while(0)

/**
 * @desc: Ensure there is enough space for values in the temp vector
 * @param self -> The vector to use
 **/
#define temporaries_ensure_space(self)                               \
  {                                                                  \
    size_t new_capacity = (self)->alloced * TEMPORARIES_GROW_FACTOR; \
    MargValue *items    = (MargValue *)collected_realloc(            \
      (self)->items, sizeof(MargValue) * new_capacity             \
    );                                                            \
                                                                     \
    if(items) {                                                      \
      (self)->alloced = new_capacity;                                \
      (self)->items   = items;                                       \
    }                                                                \
  }                                                                  \
  while(0)

/**
 * @brief Adds a new element in the temporaries vector
 * @param self -> Current vector
 * @param item -> Item to add
 */
#define temporaries_add(self, item)       \
  do {                                    \
    if((self)->alloced == (self)->size)   \
      temporaries_ensure_space((self));   \
                                          \
    (self)->items[(self)->size++] = item; \
  } while(0)

/**
 * @brief Get the value of a specific vector index
 * @param self -> Current vector
 * @param index -> Index to get the value from
 * @return MargValue
 */
#define temporaries_get(self, index) (self)->items[(index)]

/**
 * @brief Get the total number of values inserted
 * @param self -> Current vector
 * @return size_t -> Number of items in the vector
 */
#define temporaries_size(self) (self)->size

#endif
