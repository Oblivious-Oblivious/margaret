#ifndef __MARG_TENSOR_H_
#define __MARG_TENSOR_H_

#include "MargObject.h"

/**
 * @brief Defines a tensor primitive
 * @param _ -> Inherited MargObject properties
 * @param value -> A MargValue pointer array
 */
typedef struct MargTensor {
  MargObject _;
  MargValue *value;
} MargTensor;

/**
 * @brief Creates a new empty MargTensor without initial elements
 * @param vm -> A pointer to the current VM
 * @return MargTensor*
 */
MargTensor *marg_tensor_new(VM *vm);

#define marg_tensor_initialize(self)      vector_initialize(self->value)
#define marg_tensor_initialize_n(self, n) vector_initialize_n(self->value, n)
#define marg_tensor_add(self, item)       vector_add(self->value, item)
#define marg_tensor_add_tensor(self, other) \
  vector_add_vector(self->value, other->value)
#define marg_tensor_remove_n(self, index, number_of_elements) \
  vector_remove_n(self->value, index, number_of_elements)
#define marg_tensor_remove(self, index)   vector_remove(self->value, index)
#define marg_tensor_remove_last(self)     vector_remove_last(self->value)
#define marg_tensor_last(self)            vector_last(self->value)
#define marg_tensor_size(self)            vector_size(self->value)
#define marg_tensor_size_signed(self)     vector_size_signed(self->value)
#define marg_tensor_capacity(self)        vector_capacity(self->value)
#define marg_tensor_capacity_signed(self) vector_capacity_signed(self->value)
#define marg_tensor_push                  marg_tensor_add
#define marg_tensor_pop(self)             vector_pop(self->value)
#define marg_tensor_peek(self)            vector_peek(self->value)

#endif
