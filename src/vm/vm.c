#include "vm.h"

/**
 * @brief Resets the top of the stack.
 * @param vm -> Current VM 
 */
static inline void STACK_RESET(VM *vm) {
    vm->stack_top = vm->stack;
}

/**
 * @brief Defines a set of primitive messages with
    which all user defined ones will be composed from
 */
static void primitives_define(void) {
}

VM *vm_new(void) {
    VM *vm = (VM*)collected_malloc(sizeof(VM));

    vm->bytecode = chunk_new_empty();
    marg_hash_init(&vm->interned_strings);
    marg_hash_init(&vm->global_variables);
    marg_hash_init(&vm->string_constants);

    STACK_RESET(vm);
    primitives_define();

    return vm;
}
