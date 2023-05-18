#ifndef __MARGARET_PROTO_H_
#define __MARGARET_PROTO_H_

#include "vm.h"

#include "../opcode/MargObject.h"
#include "../opcode/MargString.h"

MargValue margaret_setup(VM *vm) {
    MargValue margaret = MARG_OBJECT("$Margaret");
    AS_OBJECT(margaret)->parent = AS_OBJECT(margaret);
    table_set(&AS_OBJECT(margaret)->instance_variables, MARG_STRING("@super"), margaret);
    table_set(&AS_OBJECT(margaret)->instance_variables, MARG_STRING("@self"), margaret);
    table_set(&vm->global_variables, MARG_STRING("$Margaret"), margaret);

    return margaret;
}

#endif
