#ifndef __MARG_METHOD_H_
#define __MARG_METHOD_H_

#include "MargObject.h"
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

  MargValue message_name;
  MargTensor *parameter_names;
  MargProc *proc;
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

/**
 * @brief Constructs a primitive string representation for method literals
 * @param object -> The method object
 * @return char*
 */
char *marg_method_to_string(MargMethod *object);

#endif
