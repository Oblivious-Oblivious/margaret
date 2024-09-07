#ifndef __MARG_PROC_H_
#define __MARG_PROC_H_

#include "MargMethod.h"
#include "MargObject.h"

/* TODO - Remove */

/**
 * @brief Defines a MargProc structure
 * @param _ -> Inherited object properties
 * @param bound_method -> Pointer to the method in which this proc resides
 * @param bound_proc -> Enclosing proc (for closures)
 * @param parameters -> Table of actual parameters
 * @param local_variables -> Table for method-local variables
 * @param bytecode -> List of bytecode
 * @param ip -> Instruction Pointer
 */
struct MargProc {
  MargObject _;
  MargMethod *bound_method;
  MargProc *bound_proc;

  EmeraldsHashtable parameters;
  EmeraldsHashtable local_variables;

  /* TODO - Potentially define these as `register` */
  uint8_t *bytecode;
  MargValue *temporaries;
  uint8_t *ip;
};

/**
 * @brief Creates a new MargProc object
 * @param vm -> Currect VM
 * @param bound_method -> Pointer to the bound method that this procs is defined
 * under
 * @return MargProc*
 */
MargProc *marg_proc_new(VM *vm, MargMethod *bound_method);

/**
 * @brief Constructs a primitive string representation for proc literals
 * @param object -> The proc object
 * @return char*
 */
char *marg_proc_to_string(MargProc *object);

#endif
