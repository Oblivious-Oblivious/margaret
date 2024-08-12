#ifndef __LOADER_H_
#define __LOADER_H_

#include "../vm/vm.h"

/**
 * @brief Loads a file into a VM object
 * @param vm -> The VM object
 * @return VM* -> The VM object
 */
VM *loader_load(VM *vm);

#endif
