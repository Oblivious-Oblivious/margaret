#ifndef __MARG_SYMBOL_H_
#define __MARG_SYMBOL_H_

#include "MargObject.h"

/**
 * @brief An object representation of MARG_SYMBOL
 * @param _ -> Inherited object properties
 * ...
 */
typedef struct MargSymbol {
  MargObject _;
  char *value;
} MargSymbol;

/**
 * @brief Constructs a new symbol object
 * @param vm -> A pointer to the current VM
 * @param value -> The identifier representation of the symbol
 * @return MargSymbol*
 */
MargSymbol *marg_symbol_new(VM *vm, char *value);

/**
 * @brief Casts to string
 * @param object -> The symbol object
 * @return char*
 */
char *marg_symbol_to_string(MargSymbol *object);

#endif
