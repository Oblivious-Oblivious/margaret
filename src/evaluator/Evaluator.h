#ifndef __EVALUATOR_H_
#define __EVALUATOR_H_

#include "../base/marg_string.h"
#include "../base/marg_vector.h"

typedef struct Evaluator {
    void *dummy;
} Evaluator;

/**
 * @brief Creates a new evaluator object
 * @param bytecodes -> The generated opcodes from the parser
 * @return Evaluator*
 */
Evaluator *evaluator_new(marg_vector *bytecodes);

#endif
