#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t */

#include "MargObject.h"

struct MargString {
    MargObject obj;
    size_t size;
    char *chars;
};

MargString *marg_string_copy(char *chars, size_t size);

#endif
