#include "vm.h"

#include "../opcode/MargObject.h"
#include "../opcode/MargMethod.h"
#include "../opcode/MargString.h"

/**
 * @brief Defines the main entry point of execution
 */
static void define_main_method(VM *vm) {
    MargObject *margaret = AS_OBJECT(MARG_OBJECT("$Margaret"));
    MargMethod *method = AS_METHOD(MARG_METHOD(margaret, "main:"));
    table_set(&margaret->messages, MARG_STRING("main:"), QNAN_BOX(method));
    table_set(&vm->global_variables, MARG_STRING("$Margaret"), QNAN_BOX(margaret));
    vm->current = method->proc;

    MargValue nil_singleton = MARG_OBJECT("$nil");
    AS_OBJECT(nil_singleton)->parent = margaret;
    table_set(&vm->global_variables, MARG_STRING("$nil"), nil_singleton);

    MargValue false_singleton = MARG_OBJECT("$false");
    AS_OBJECT(false_singleton)->parent = margaret;
    table_set(&vm->global_variables, MARG_STRING("$false"), false_singleton);

    MargValue true_singleton = MARG_OBJECT("$true");
    AS_OBJECT(true_singleton)->parent = margaret;
    table_set(&vm->global_variables, MARG_STRING("$true"), true_singleton);

    MargValue integer_proto = MARG_OBJECT("$IntegerProto");
    AS_OBJECT(integer_proto)->parent = margaret;
    table_set(&vm->global_variables, MARG_STRING("$IntegerProto"), integer_proto);

    MargValue float_proto = MARG_OBJECT("$FloatProto");
    AS_OBJECT(float_proto)->parent = margaret;
    table_set(&vm->global_variables, MARG_STRING("$FloatProto"), float_proto);
}

VM *vm_new(void) {
    VM *vm = (VM*)collected_malloc(sizeof(VM));

    vm->sp = vm->stack;
    table_init(&vm->global_variables);
    table_init(&vm->interned_strings);

    define_main_method(vm);

    return vm;
}
