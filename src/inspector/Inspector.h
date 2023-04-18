#ifndef __INSPECTOR_H_
#define __INSPECTOR_H_

#include "../vm/vm.h"

/**
 * @brief Disassembles a bytecode chunk and inspects the content
 * @param vm -> The vm to be disassembled
 * @return marg_vector* -> The list of disassembled
    instructions as marg_strings (for testing)
 */
marg_vector *inspect_vm_bytecode(VM *vm);

/**
 * @brief Prints without returning inspection results
 * @param vm -> The vm to be disassembled
 */
void inspect_and_print_vm_bytecode(VM *vm);

#endif
