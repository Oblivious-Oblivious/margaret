#ifndef __MARG_STRING_H_
#define __MARG_STRING_H_

#include <stdlib.h> /* size_t */

#include "MargObject.h"

struct ObjString {
    Obj obj;
    size_t size;
    char *chars;
};

ObjString *obj_string_copy(char *chars, size_t size);

#endif
