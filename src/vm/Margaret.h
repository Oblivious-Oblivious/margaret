#ifndef __MARGARET_PRIMITIVE_H_
#define __MARGARET_PRIMITIVE_H_

#include "../opcode/MargString.h"
#include "../opcode/MargObject.h"
#include "../opcode/MargMethod.h"

static void primitive_1_margaret_main(VM *vm, MargObject *object) {
    table_set(&object->messages, MARG_STRING("main:"), MARG_METHOD(object, "main:"));
}

#endif
