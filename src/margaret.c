/**
 * An object oriented language system based on ruby and smalltalk.
 *
 * Copyright (C) 2024 Athanasios Papapostolou (oblivious)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "version.h"
#include "vm/compilation_pipeline.h"

#include <stdio.h> /* printf */

/* TODO - Eventually merge emmiter with parser placing formalizer behind flag */

p_inline void margaret_repl(VM *vm) {
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
}

p_inline void margaret_run_file(VM *vm) {
  EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(LOAD(vm))))));
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
