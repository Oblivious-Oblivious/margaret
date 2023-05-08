#ifndef __MARG_PROC_H_
#define __MARG_PROC_H_

#include "../base/chunk.h"
#include "../base/table.h"

#include "MargObject.h"
#include "MargMethod.h"

struct MargProc {
    MargObject _;
    MargMethod *bound_method;
    MargProc *bound_proc;

    table parameters;
    table *global_variables;
    table *instance_variables;
    table local_variables;

    chunk *bytecode;
    uint8_t *ip;
};

MargProc *marg_proc_new(VM *vm, MargMethod *bound_method);

#endif
