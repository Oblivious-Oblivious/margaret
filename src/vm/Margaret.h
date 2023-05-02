#ifndef __MARGARET_PRIMITIVE_H_
#define __MARGARET_PRIMITIVE_H_

#include "../opcode/MargString.h"
#include "../opcode/MargObject.h"
#include "../opcode/MargMethod.h"

static void primitive_1_margaret_main(VM *vm) {
    MargObject *object = AS_OBJECT(MARG_OBJECT("$Margaret", 10));
    MargMethod *method = AS_METHOD(MARG_METHOD(object));
    method->proc = AS_PROC(MARG_PROC(method));

    table_set(&object->messages, MARG_STRING("main:", 6), QNAN_BOX(method));
    table_set(&vm->global_variables, MARG_STRING("$Margaret", 10), QNAN_BOX(object));
}

#endif
