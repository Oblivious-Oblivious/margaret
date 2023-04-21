#ifndef __MARG_OBJECT_H_
#define __MARG_OBJECT_H_

#include <stdlib.h> /* size_t */

typedef struct MargObject MargObject;
typedef struct MargString MargString;

typedef enum {
    MARG_STRING,
} MargObjectType;

struct MargObject {
    MargObjectType type;
};

MargObject *marg_object_allocate(size_t size, MargObjectType type);

#endif
