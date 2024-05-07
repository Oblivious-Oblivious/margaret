#ifndef __MARG_TENSOR_H_
#define __MARG_TENSOR_H_

#include "MargObject.h"

#define MARG_TENSOR_GROW_FACTOR 1.618

/**
 * @brief Defines a tensor primitive
 * @param _ -> Inherited MargObject properties
 * @param items -> A MargValue pointer array
 * @param alloced -> Total capacity of the tensor
 * @param size -> Total number of values
 */
typedef struct MargTensor {
  MargObject _;

  MargValue *items;
  size_t alloced;
  size_t size;
} MargTensor;

/**
 * @brief Creates a new empty MargTensor without initial elements
 * @param vm -> A pointer to the current VM
 * @param initial_size -> User chooses starting length
 * @return MargTensor*
 */
MargTensor *marg_tensor_new(VM *vm, size_t initial_size);

/**
 * @desc: Ensure there is enough space for values in the tensor
 * @param self -> The tensor to use
 **/
#define marg_tensor_ensure_space(self)                               \
  do {                                                               \
    size_t new_capacity = (self)->alloced * MARG_TENSOR_GROW_FACTOR; \
    MargValue *items    = (MargValue *)collected_realloc(            \
      (self)->items, sizeof(MargValue) * new_capacity             \
    );                                                            \
                                                                     \
    if(items) {                                                      \
      (self)->alloced = new_capacity;                                \
      (self)->items   = items;                                       \
    }                                                                \
  } while(0)

/**
 * @brief Adds a new element in the MargTensor
 * @param self -> Current tensor
 * @param item -> Item to add
 */
#define marg_tensor_add(self, item)       \
  do {                                    \
    if((self)->alloced == (self)->size)   \
      marg_tensor_ensure_space((self));   \
                                          \
    (self)->items[(self)->size++] = item; \
  } while(0)

/**
 * @brief Adds a new element in a specific position
 * @param self -> Current tensor
 * @param item -> Item to add
 * @param index -> Index to add to
 */
#define marg_tensor_add_at(self, item, index) \
  do {                                        \
    if((self)->alloced == (self)->size)       \
      marg_tensor_ensure_space((self));       \
                                              \
    (self)->items[index] = item;              \
    (self)->size++;                           \
  } while(0)

/**
 * @brief Deletes an element from the tensor
 * @param self -> Current tensor
 * @param index -> Index to remove from
 */
#define marg_tensor_delete(self, index) (self)->items[--(self)->size] = NULL;

/**
 * @brief Get the value of a specific tensor index
 * @param self -> Current tensor
 * @param index -> Index to get the value from
 * @return MargValue
 */
#define marg_tensor_get(self, index) (self)->items[(index)]

/**
 * @brief Get the total number of values inserted in the tensor
 * @param self -> Current tensor
 * @return size_t -> Number of items in the tensor
 */
#define marg_tensor_size(self) (self)->size

/**
 * @brief String representation for tensor literals in the Java style
 * @param object -> The tensor object as a MargValue
 * @return char*
 */
char *marg_tensor_to_string(MargValue object);

#endif
