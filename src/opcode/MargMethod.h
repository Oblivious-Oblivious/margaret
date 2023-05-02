#ifndef __MARG_METHOD_H_
#define __MARG_METHOD_H_

#include "MargObject.h"
#include "MargProc.h"

struct MargMethod {
    MargObject _;
    MargProc *proc;

    MargObject *bound_object;
};

MargMethod *marg_method_new(VM *vm, MargObject *bound_object);

#endif
