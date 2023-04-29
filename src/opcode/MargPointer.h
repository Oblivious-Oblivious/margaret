#ifndef __MARG_POINTER_H_
#define __MARG_POINTER_H_

// TODO docs comment all function definitions and structs

#include <stdlib.h> /* size_t */

typedef enum {
    MARG_NIL_TYPE,
    MARG_FALSE_TYPE,
    MARG_TRUE_TYPE,
    MARG_INTEGER_TYPE,
    MARG_FLOAT_TYPE,
    MARG_STRING_TYPE,
} MargPointerType;

typedef struct MargPointer {
    MargPointerType type;
} MargPointer;

MargPointer *marg_pointer_new(size_t size, MargPointerType type);

#endif
