#ifndef __MARG_PROC_H_
#define __MARG_PROC_H_

#include "../base/table.h"

#include "MargObject.h"
#include "ActivationRecord.h"
#include "MargMethod.h"

struct MargProc {
    MargObject _;
    table parameters;
    MargMethod *bound_method;
    ActivationRecord *code;
};

MargProc *marg_proc_new(table *global_variables, MargMethod *bound_method);

#endif
