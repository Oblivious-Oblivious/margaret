#ifndef __MARG_VALUE_TYPE_H_
#define __MARG_VALUE_TYPE_H_

#include <stddef.h> /* size_t */

/** @brief Ex nihilo value */
typedef size_t MargValue;

/** @brief Instruction size */
typedef size_t Instruction;

/** @brief Maximum number of registers */
#define MAX_REGISTERS (1 << 16)

#endif
