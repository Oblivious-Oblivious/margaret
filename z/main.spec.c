#include "primitives.spec.h"
#include "vm.spec.h"

int main(void) {
  cspec_run_suite("all", {
    primitives_spec();
    vm_spec();
  });
}
