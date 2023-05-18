#ifndef __FALSE_SINGLETON_H_
#define __FALSE_SINGLETON_H_

#include "proto_helpers.h"

MargValue false_singleton_setup(VM *vm, MargValue parent) {
    MargValue false_singleton = create_new_proto_object(vm, parent, "$false");

    return false_singleton;
}

#endif
