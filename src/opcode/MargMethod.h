#ifndef __MARG_METHOD_H_
#define __MARG_METHOD_H_

#include "MargString.h"
#include "MargTensor.h"

/**
 * @brief Defines a MargMethod object
 * @param _ -> Inherited object properties
 * @param bound_object -> Pointer to the bound object this method is defined
 * under
 * @param message_name -> String representation of the message name derived by
 * the parsed method
 * @param parameter_names -> A Tensor that saves formal parameter names
 * @param proc -> The proc this method executes (Encapsulates the activation
 * record)
 */
typedef struct MargMethod {
  MargObject _;
  MargObject *bound_object;
  struct MargMethod *bound_method;

  MargString *message_name;
  MargTensor *parameter_names;
  MargValue *temporaries;
  EmeraldsTable local_variables;
  /* TODO - Potentially define these as `register` */
  uint8_t *bytecode;
  uint8_t *ip;
  uint8_t *sp;

  struct MargProc *proc; /* TODO - Remove */
} MargMethod;

/**
 * @brief Creates a new MargMethod object
 * @param vm -> Current VM
 * @param bound_object
 * @param message_name
 * @return MargMethod*
 */
MargMethod *
marg_method_new(VM *vm, MargObject *bound_object, char *message_name);

#endif
