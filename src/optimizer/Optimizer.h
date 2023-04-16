#ifndef __OPTIMIZER_H_
#define __OPTIMIZER_H_

#include "../base/marg_stack.h"
#include "../opcode/Chunk.h"

typedef struct Optimizer {
    marg_stack stack;
    Chunk *bytecode;
} Optimizer;

/**
 * @brief Initializes a new optimizer
 * @param bytecode -> Receives emitted bytecode chunks
 * @return Optimizer* -> The Optimizer object
 */
Optimizer *optimizer_new(Chunk *bytecode);

/**
 * @brief Runs the iterator that transforms
    into scoped emitted bytecode
 * @param self -> The Emitter object
 * @return Chunk* -> The new intermediate bytecode
 */
Chunk *optimizer_optimize(Optimizer *self);

#endif
