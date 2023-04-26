#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

// TODO docs comment all function definitions and structs

#include <stdlib.h> /* size_t */

typedef struct MargObject MargObject;
typedef struct MargString MargString;

typedef enum {
    MARG_NIL_TYPE,
    MARG_FALSE_TYPE,
    MARG_TRUE_TYPE,
    MARG_STRING_TYPE,
} MargObjectType;

struct MargObject {
    MargObjectType type;
};

MargObject *marg_object_allocate(size_t size, MargObjectType type);

#endif
