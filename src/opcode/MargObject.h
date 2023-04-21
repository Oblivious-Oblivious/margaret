#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

#include <stdlib.h> /* size_t */

typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum {
    OBJ_STRING,
} ObjType;

struct Obj {
    ObjType type;
};

Obj* obj_allocate(size_t size, ObjType type);

#endif
