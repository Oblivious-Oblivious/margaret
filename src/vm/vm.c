#include "vm.h"

#include "../opcode/MargObject.h"
#include "../opcode/MargMethod.h"
#include "../opcode/MargString.h"

/**
 * @brief Creates a proto object with a predefined parent slot.
    Sets up @self and @super instances and initially has no methods.
    Proto chain is always global.
 * @param vm -> Current vm
 * @param parent -> Parent object to bind to
 * @param name -> Name of the new proto
 * @return MargValue -> New object value
 */
MargValue create_new_proto_object(VM *vm, MargValue parent, char *name) {
    MargValue proto_object = MARG_OBJECT(name);
    AS_OBJECT(proto_object)->parent = AS_OBJECT(parent);
    table_set(&AS_OBJECT(proto_object)->instance_variables, MARG_STRING("@self"), proto_object);
    table_set(&AS_OBJECT(proto_object)->instance_variables, MARG_STRING("@super"), parent);
    table_set(&vm->global_variables, MARG_STRING(name), proto_object);

    return proto_object;
}

MargValue margaret_setup(VM *vm) {
    MargValue margaret = MARG_OBJECT("$Margaret");
    AS_OBJECT(margaret)->parent = AS_OBJECT(margaret);
    table_set(&AS_OBJECT(margaret)->instance_variables, MARG_STRING("@super"), margaret);
    table_set(&AS_OBJECT(margaret)->instance_variables, MARG_STRING("@self"), margaret);
    table_set(&vm->global_variables, MARG_STRING("$Margaret"), margaret);

    return margaret;
}

/**
 * @brief Sets up the delegation chain of proto objects
    and defines rudimentary messages like self and super
 * @param vm -> Current vm
 */
static void setup_proto_object_chain(VM *vm) {
    MargValue margaret = margaret_setup(vm);

    create_new_proto_object(vm, margaret, "$nil");
    create_new_proto_object(vm, margaret, "$false");
    create_new_proto_object(vm, margaret, "$true");

    MargValue numeric_proto = create_new_proto_object(vm, margaret, "$NumericProto");
    create_new_proto_object(vm, numeric_proto, "$IntegerProto");
    create_new_proto_object(vm, numeric_proto, "$FloatProto");

    create_new_proto_object(vm, margaret,  "$StringProto");

    MargValue enumerable_proto = create_new_proto_object(vm, margaret, "$EnumerableProto");
    create_new_proto_object(vm, enumerable_proto, "$TensorProto");
    // create_new_proto_object(vm, tensor_proto, "$TupleProto");
    create_new_proto_object(vm, enumerable_proto, "$HashProto");
    // create_new_proto_object(vm, enumerable_proto, "$BitstringProto");

    create_new_proto_object(vm, margaret, "$MethodProto");
    create_new_proto_object(vm, margaret, "$ProcProto");
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
