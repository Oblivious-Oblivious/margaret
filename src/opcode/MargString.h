#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint64_t */

#include "MargObject.h"

typedef struct MargString {
    MargObject _;
    size_t size;
    uint64_t hash;
    char chars[];
} MargString;

MargString *marg_string_new(VM *vm, char *chars, size_t size);

#endif
