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

  char *message_name;

  char **arguments;
  MargValue *constants;
  EmeraldsTable local_variables;
  uint8_t *bytecode;

  /* TODO - Potentially define these as `register` */
  uint8_t *ip;
  uint8_t *sp;
} MargMethod;

/**
 * @brief Creates a new MargMethod object
 * @param vm -> Current VM
 * @param bound_object
 * @param message_name
 * @return MargMethod*
 */
MargMethod *marg_method_new(VM *vm, MargValue bound_object, char *message_name);

#endif
