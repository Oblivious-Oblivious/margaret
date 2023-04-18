#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../base/marg_vector.h"
#include "../vm/vm.h"

/**
 * @brief Runs the iterator that transforms
    into scoped emitted bytecode
 * @param self -> The Emitter object
 * @return VM* -> The new VM object
 */
VM *emitter_emit(marg_vector *formal_bytecode);

#endif
