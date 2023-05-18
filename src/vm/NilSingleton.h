#ifndef __NIL_SINGLETON_H_
#define __NIL_SINGLETON_H_

#include "proto_helpers.h"

MargValue nil_singleton_setup(VM *vm, MargValue parent) {
    MargValue nil_singleton = create_new_proto_object(vm, parent, "$nil");

    return nil_singleton;
}

#endif
