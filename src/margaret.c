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

#include "vm/on_demand_compilation_pipeline.h"

#include <stdio.h> /* printf */

#define VERSION "0.0.1"
#define DATE    "2022-2024"
#define LINK    "margaret.org"

// TODO - Replace int, long, size_t etc. values with bit equivalents (uint64_t)

static void margaret_repl(VM *vm) {
  printf("Margaret %s  Copyright (C) %s %s, Ioannina\n", VERSION, DATE, LINK);
  while(true) {
    PRINT(EVAL(OPTIMIZE(EMIT(vm, FORMALIZE(READ(SCAN("> "), "repl"))))));
  }
}

static void margaret_run_file(VM *vm, char *filename) {
  char *chars            = LOAD(filename);
  Token **tokens         = READ(chars, filename);
  char **formal_bytecode = FORMALIZE(tokens);
  // PRINT_FORMAL(formal_bytecode);
  vm                     = EMIT(vm, formal_bytecode);
  vm                     = OPTIMIZE(vm);
  EVAL(vm);
}

int main(int argc, char **argv) {
  VM *vm = vm_new();
  if(argc < 2) {
    (void)argc;
    (void)argv;
    margaret_repl(vm);
  } else {
    margaret_run_file(vm, argv[1]);
  }
}
