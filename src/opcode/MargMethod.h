#ifndef __MARG_METHOD_H_
#define __MARG_METHOD_H_

#include "MargString.h"
#include "MargTensor.h"

/**
 * @brief Defines a MargMethod object
 * @param _ -> Inherited object properties
 *
 * @param bound_object -> Points to bound object this method is defined under
 * @param bound_method -> Points to the enclosing method
 *
 * @param message_name -> Name of current message derived by the parsed method
 *
 * @param arguments -> A Tensor that saves formal argument names
 * @param constants -> A Tensor that saves intermediate values
 * @param local_variables -> A table for method-local variables
 * @param bytecode -> Bytecode array
 *
 * @param ip -> Instruction Pointer
 * @param sp -> Stack pointer
 */
typedef struct MargMethod {
  MargObject _;

  MargObject *bound_object;
  struct MargMethod *bound_method;

  const char *message_name;

  MargValue local_registers[MAX_REGISTERS];
  uint32_t local_index;
  MargValue *constants;
  EmeraldsTable local_variables;

  Instruction *bytecode;
  Instruction ip;
} MargMethod;

/**
 * @brief Creates a new MargMethod object
 * @param vm -> Current VM
 * @param bound_object
 * @param bound_method
 * @param message_name
 * @return MargMethod*
 */
MargMethod *marg_method_new(
  VM *vm,
  MargObject *bound_object,
  MargMethod *bound_method,
  const char *message_name
);

#endif
