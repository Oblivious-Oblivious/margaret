#ifndef __TRUE_SINGLETON_H_
#define __TRUE_SINGLETON_H_

#include "proto_helpers.h"

MargValue true_singleton_setup(VM *vm, MargValue parent) {
    MargValue true_singleton = create_new_proto_object(vm, parent, "$true");

    return true_singleton;
}

#endif
