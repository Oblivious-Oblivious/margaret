#ifndef __MARG_METHOD_H_
#define __MARG_METHOD_H_

#include "MargObject.h"
#include "MargProc.h"

struct MargMethod {
    MargObject _;
    MargObject *bound_object;

    MargValue message_name;
    MargValue parameter_names;
    MargProc *proc;
};

MargMethod *marg_method_new(VM *vm, MargObject *bound_object, char *message_name);

#endif
