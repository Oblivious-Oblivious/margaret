#include "vm.h"

#include "Margaret.h"

static void Margaret_primitives(VM *vm) {
    MargObject *object = AS_OBJECT(MARG_OBJECT("$Margaret"));

    primitive_1_margaret_main(vm, object);

    table_set(&vm->global_variables, MARG_STRING("$Margaret"), QNAN_BOX(object));
}

static void set_initial_current_record_to_main(VM *vm) {
    MargObject *marg = AS_OBJECT(table_get(&vm->global_variables, MARG_STRING("$Margaret")));
    MargMethod *main = AS_METHOD(table_get(&marg->messages, MARG_STRING("main:")));
    vm->current = main->proc->activation_record;
}

/**
 * @brief Defines a set of primitive messages with
    which all user defined ones will be composed from
 */
static void primitives_define(VM *vm) {
    Margaret_primitives(vm);
    // nil_primitives(vm);
    // true_primitives(vm);
    // false_primitives(vm);
    // Integer_primitives(vm);
    // Float_primitives(vm);
    // String_primitives(vm);

    set_initial_current_record_to_main(vm);
}

VM *vm_new(void) {
    VM *vm = (VM*)collected_malloc(sizeof(VM));

    vm->sp = vm->stack;
    table_init(&vm->global_variables);
    table_init(&vm->interned_strings);

    primitives_define(vm);

    return vm;
}
