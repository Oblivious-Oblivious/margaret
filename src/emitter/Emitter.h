#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../vm/vm.h"

/**
 * @brief Runs the iterator that transforms
    into scoped emitted bytecode
 * @param self -> The Emitter object
 * @param vm -> The new vm object
 * @param formal_bytecode
 * @return VM* -> The modified VM object
 */
VM *emitter_emit(VM *vm);

#endif
