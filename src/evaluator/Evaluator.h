#ifndef __EVALUATOR_H_
#define __EVALUATOR_H_

#include "../vm/vm.h"

/**
 * @brief Evaluates the final optimized version of bytecode instructions
 * @param self -> Current VM
 * @return The MargValue result on the top of the stack
 */
MargValue evaluator_evaluate(VM *self);

#endif
