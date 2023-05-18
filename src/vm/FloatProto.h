#ifndef __FLOAT_PROTO_H_
#define __FLOAT_PROTO_H_

#include "proto_helpers.h"

MargValue float_proto_setup(VM *vm, MargValue parent) {
    MargValue float_proto = create_new_proto_object(vm, parent, "$FloatProto");

    return float_proto;
}

#endif
