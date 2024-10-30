#include "emitter.h"
#include "evaluator.h"

int main(void) {
  VM vm = {0};
  vm_init(&vm);

  emit_example_bytecode(&vm);
  evaluate(&vm);
}
