#ifndef __INTEGER_PROTO_H_
#define __INTEGER_PROTO_H_

#include "proto_helpers.h"

MargValue integer_proto_setup(VM *vm, MargValue parent) {
    MargValue integer_proto = create_new_proto_object(vm, parent, "$IntegerProto");

    return integer_proto;
}

#endif
