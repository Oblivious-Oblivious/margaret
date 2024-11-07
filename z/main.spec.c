#include "vm.spec.h"

int main(void) {
  cspec_run_suite("all", { vm_spec(); });
}
