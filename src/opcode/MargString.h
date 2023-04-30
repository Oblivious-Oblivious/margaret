#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t */
#include <stdint.h> /* uint64_t */

#include "MargPointer.h"

typedef struct MargString {
    MargPointer _;
    size_t size;
    uint64_t hash;
    char chars[];
} MargString;

MargString *marg_string_new(char *chars, size_t size);

#endif
