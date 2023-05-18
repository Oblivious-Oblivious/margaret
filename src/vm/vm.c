#include "vm.h"

#include "../opcode/MargMethod.h"

#include "Margaret.h"

#include "NilSingleton.h"
#include "FalseSingleton.h"
#include "TrueSingleton.h"

#include "NumericProto.h"
#include "IntegerProto.h"
#include "FloatProto.h"

/**
 * @brief Sets up the delegation chain of proto objects
    and defines rudimentary messages like self and super
 * @param vm -> Current vm
 */
static void setup_proto_object_chain(VM *vm) {
    MargValue margaret = margaret_setup(vm);

    nil_singleton_setup(vm, margaret);
    false_singleton_setup(vm, margaret);
    true_singleton_setup(vm, margaret);

    MargValue numeric_proto = numeric_proto_setup(vm, margaret);
    integer_proto_setup(vm, numeric_proto);
    float_proto_setup(vm, numeric_proto);
}

/**
 * @brief Defines the main entry point of execution
 * @param vm -> Current vm
 */
static void define_main_method(VM *vm) {
    MargObject *margaret = AS_OBJECT(table_get(&vm->global_variables, MARG_STRING("$Margaret")));
    MargMethod *method = AS_METHOD(MARG_METHOD(margaret, "main:"));
    table_set(&margaret->messages, MARG_STRING("main:"), QNAN_BOX(method));
    vm->current = method->proc;
}

VM *vm_new(void) {
    VM *vm = (VM*)collected_malloc(sizeof(VM));

    vm->sp = vm->stack;
    table_init(&vm->global_variables);
    table_init(&vm->interned_strings);

    setup_proto_object_chain(vm);
    define_main_method(vm);

    return vm;
}
