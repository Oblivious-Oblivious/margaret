#ifndef __HELPERS_SPEC_H_
#define __HELPERS_SPEC_H_

#include "vm.h"

static VM _vm = {0};
static VM *vm = &_vm;
static void reset_vm(void) { vm_init(vm); }

#endif
