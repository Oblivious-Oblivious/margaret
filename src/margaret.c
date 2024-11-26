/**
 * @author oblivious (https://www.dreamnotexpiring.com/about)
 * @brief An pure OOP system (https://www.margaret-lang.org)
 * @date Copyright (C) 2022-2025 Athanasios Papapostolou (oblivious)
 * @copyright Margaret by oblivious is marked with MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
