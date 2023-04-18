#ifndef __OPTIMIZER_H_
#define __OPTIMIZER_H_

#include "../vm/vm.h"

/**
 * @brief Optimizes bytecodes by directly changing vm data
 * @param self -> VM
 * @return VM* -> VM
 */
VM *optimizer_optimize(VM *self);

#endif
