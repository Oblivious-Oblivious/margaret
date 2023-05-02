#ifndef __ACTIVATION_RECORD_H_
#define __ACTIVATION_RECORD_H_

#include <stdint.h> /* uint8_t */
#include "../base/chunk.h"
#include "../base/table.h"
#include "MargProc.h"
#include "../vm/vm.h"

struct ActivationRecord {
    chunk *bytecode;
    uint8_t *ip;
    table local_variables;

    MargProc *bound_proc;
    table *instance_variables;
    table *global_variables;
};

ActivationRecord *activation_record_new(MargProc *bound_proc);

#endif

// Suppose Integer has "+" and "neg" as primitives
//     (Integer + Integer)
//     (Integer neg)

// Integer contains:
//     Integer: {
//         messages: {
//             "+": [m1, m2],
//             "neg": [m1]
//         }
//     }

// When we bind a new method:
//     Integer bind: # - other => self + other neg

// Results in:
//     onmethoddef {
//         Method { name: "-", proc: { self | self + other neg }, bound_object: NULL}
//     }
//     onbind {
//         Method.bound_object = Object,
//         table_add(Object.messages, Method.name, Method.proc),
//     }

// Now Integer is updated:
//     Integer {
//         messages: {
//             "+": [m1, m2],
//             "neg": [m1],
//             "-": [m1]
//         }
//     }
