/**
 * @author oblivious (https://www.dreamnotexpiring.com)
 * @brief A developer's only tool (https://www.margaret-lang.org)
 * @date Copyright (C) 2022-2024 Athanasios Papapostolou (oblivious)
 * @copyright Margaret by oblivious is marked with CC0 1.0 Universal
 */

#include "version.h"
#include "vm/compilation_pipeline.h"

#include <stdio.h> /* printf */

/* TODO - Eventually merge emmiter with parser placing formalizer behind flag */

static void margaret_repl(VM *vm) {
  printf(
    "Margaret %s  Copyright (C) %s %s, %s\n",
    MARGARET_VERSION,
    MARGARET_DATE,
    MARGARET_LINK,
    MARGARET_CITY
  );
  while(true) {
    PRINT(EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(SCAN(vm, "> ")))))));
  }
  vm_free();
}

static void margaret_run_file(VM *vm) {
  EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(LOAD(vm))))));
  vm_free();
}

int main(int argc, char **argv) {
  if(argc < 2) {
    (void)argc;
    (void)argv;
    margaret_repl(vm_new("repl"));
  } else {
    margaret_run_file(vm_new(argv[1]));
  }
}
