#ifndef __INSPECTOR_H_
#define __INSPECTOR_H_

#include "../vm/vm.h"

/**
 * @brief Disassembles a bytecode vector and inspects the content
 * @param vm -> The vm to be disassembled
 * @return vector* -> The list of disassembled
    instructions as marg_strings (for testing)
 */
char **inspect_vm_bytecode(VM *vm);

/**
 * @brief Prints without returning inspection results
 * @param vm -> The vm to be disassembled
 */
void inspect_and_print_vm_bytecode(VM *vm);

/**
 * @brief Inspects a proc
 * @param vm -> The vm to be disassembled
    Assuming that ip now points to a proc activation record
 */
void inspect_and_print_proc(VM *vm);

/**
 * @brief Inspects a proc
 * @param vm -> The vm to be disassembled
    Assuming that ip now points to a method activation record
 */
void inspect_and_print_method(VM *vm);

/**
 * @brief Inspects the main method ($Margaret main)
 * @param vm -> The vm to be disassembled
 */
void inspect_and_print_main(VM *vm);

#endif
