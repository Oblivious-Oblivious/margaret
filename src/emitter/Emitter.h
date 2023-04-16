#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../base/marg_stack.h"
#include "../base/marg_vector.h"

#include "../opcode/Chunk.h"

typedef struct Emitter {
    marg_stack stack;
    marg_vector *bytecode;
} Emitter;

/**
 * @brief Initializes a new emitter
 * @param bytecode -> Receives FormalMessagesBytecode
 * @return Emitter* -> The Emitter object
 */
Emitter *emitter_new(marg_vector *bytecode);

/**
 * @brief Runs the iterator that transforms
    into scoped emitted bytecode
 * @param self -> The Emitter object
 * @return Chunk* -> The new intermediate bytecode
 */
Chunk *emitter_emit(Emitter *self);

#endif
