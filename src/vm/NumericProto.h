#ifndef __NUMERIC_PROTO_H_
#define __NUMERIC_PROTO_H_

#include "proto_helpers.h"

MargValue numeric_proto_setup(VM *vm, MargValue parent) {
    MargValue numeric_proto = create_new_proto_object(vm, parent, "$NumericProto");

    return numeric_proto;
}

#endif
