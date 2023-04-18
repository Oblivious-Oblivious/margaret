#ifndef __EVALUATOR_H_
#define __EVALUATOR_H_

#include "../vm/vm.h"

/**
 * @brief Returns according to runtime results
 */
typedef enum EvaluatorResult {
    EVALUATOR_OK,
    EVALUATOR_COMPILE_ERROR,
    EVALUATOR_RUNTIME_ERROR
} EvaluatorResult;

/**
 * @brief Evaluates the final optimized version of bytecode instructions
 * @param self -> Current VM
 * @return
 */
MargValue evaluator_evaluate(VM *self);

#endif
