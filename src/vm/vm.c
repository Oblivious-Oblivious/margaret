#include "vm.h"

#include "../opcode/MargString.h"

/**
 * @brief Defines the main entry point of execution
 */
static void define_main_method(VM *vm) {
    MargObject *object = AS_OBJECT(MARG_OBJECT("$Margaret"));
    MargMethod *method = AS_METHOD(MARG_METHOD(object, "main:"));
    table_set(&object->messages, MARG_STRING("main:"), QNAN_BOX(method));
    table_set(&vm->global_variables, MARG_STRING("$Margaret"), QNAN_BOX(object));
    vm->current = method->proc;
}

VM *vm_new(void) {
    VM *vm = (VM*)collected_malloc(sizeof(VM));

    vm->sp = vm->stack;
    table_init(&vm->global_variables);
    table_init(&vm->interned_strings);

    define_main_method(vm);

    return vm;
}
