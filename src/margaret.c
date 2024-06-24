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

#include "opcode/MargValue.h"
#include "scanner/Scanner.h"
#include "vm/on_demand_compilation_pipeline.h"

#include <stdio.h> /* printf */

#define VERSION "0.0.1"
#define DATE    "2022-2024"
#define LINK    "margaret.org"

static char *SCAN(char *prompt) { return scanner_scan(prompt); }

static void PRINT(MargValue evaluated) {
  printf("%s\n", marg_value_format(evaluated));
}

static void PRINT_FORMAL(char **formal_bytecode) {
  printf("[");
  size_t formal_bytecode_size = vector_size(formal_bytecode);
  if(formal_bytecode_size > 0) {
    for(size_t i = 0; i < formal_bytecode_size - 1; i++) {
      printf("%s, ", formal_bytecode[i]);
    }
    printf("%s", formal_bytecode[formal_bytecode_size - 1]);
  }
  printf("]\n");
}

static void margaret_repl(VM *vm) {
  printf("Margaret %s  Copyright (C) %s %s, Ioannina\n", VERSION, DATE, LINK);
  while(true) {
    char **formal_bytecode = FORMALIZE(READ(SCAN("> "), "repl"));
    // PRINT_FORMAL(formal_bytecode);
    PRINT(EVAL(OPTIMIZE(EMIT(vm, formal_bytecode))));
  }
}

static void margaret_run_file(VM *vm, char *filename) {
  char *chars            = LOAD(filename);
  TokenTable *tokens     = READ(chars, filename);
  char **formal_bytecode = FORMALIZE(tokens);
  // PRINT_FORMAL(formal_bytecode);
  vm                     = EMIT(vm, formal_bytecode);
  vm                     = OPTIMIZE(vm);
  EVAL(vm);
}

static void banner(void) { printf("Usage: margaret <filename>\n"); }

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
