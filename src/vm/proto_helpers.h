#ifndef __PROTO_HELPERS_H_
#define __PROTO_HELPERS_H_

#include "vm.h"

#include "../opcode/MargObject.h"
#include "../opcode/MargString.h"

MargValue create_new_proto_object(VM *vm, MargValue parent, char *name) {
    MargValue proto_object = MARG_OBJECT(name);
    AS_OBJECT(proto_object)->parent = AS_OBJECT(parent);
    table_set(&AS_OBJECT(proto_object)->instance_variables, MARG_STRING("@self"), proto_object);
    table_set(&AS_OBJECT(proto_object)->instance_variables, MARG_STRING("@super"), parent);
    table_set(&vm->global_variables, MARG_STRING(name), proto_object);

    return proto_object;
}

#endif
