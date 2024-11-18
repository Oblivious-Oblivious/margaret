#include "instruction.spec.h"
#include "object.spec.h"
#include "primitives.spec.h"
#include "vm.spec.h"

int main(void) {
  cspec_run_suite("all", {
    instruction_spec();
    object_spec();
    primitives_spec();
    vm_spec();
  });
}
