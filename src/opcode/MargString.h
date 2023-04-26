#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t, uint64_t */

#include "MargObject.h"

struct MargString {
    MargObject _;
    size_t size;
    uint64_t hash;
    char chars[];
};

uint64_t marg_string_hash(char *key, size_t size);

MargString *marg_string_new(char *chars, size_t size);

#endif
