#include "vm.h"

/**
 * @brief Resets the top of the stack.
 * @param vm -> Current VM 
 */
static inline void STACK_RESET(VM *vm) {
    vm->sp = vm->stack;
}

/**
 * @brief Defines a set of primitive messages with
    which all user defined ones will be composed from
 */
static void primitives_define(void) {
}

VM *vm_new(void) {
    VM *vm = (VM*)collected_malloc(sizeof(VM));

    vm->bytecode = chunk_new();
    table_init(&vm->interned_strings);
    table_init(&vm->global_variables);

    STACK_RESET(vm);
    primitives_define();

    return vm;
}

void vm_free(VM *vm) {
    // TODO
    (void)vm;
    // chunk_free(vm->bytecode);
    // table_free(&vm->interned_strings);
    // table_free(&vm->global_variables);
}
