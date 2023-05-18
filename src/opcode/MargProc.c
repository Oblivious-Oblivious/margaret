#include "MargProc.h"

#include "../opcode/MargString.h"

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
    MargObject *obj = marg_object_new(vm, sizeof(MargProc), "$Proc");
    MargProc *self = (MargProc*)obj;

    MargValue proto_object = table_get(&vm->global_variables, MARG_STRING("$ProcProto"));
    obj->parent = AS_OBJECT(proto_object);

    self->bound_method = bound_method;
    self->bound_proc = bound_method->proc;

    table_init(&self->parameters);
    table_init(&self->local_variables);

    self->bytecode = chunk_new();
    self->ip = self->bytecode->items;

    return self;
}
