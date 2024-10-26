#include "instruction.spec.h"

int main(void) {
  cspec_run_suite("all", { instruction_format_spec(); });
}
