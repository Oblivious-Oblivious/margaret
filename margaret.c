// Copyright (C) 2024 Athanasios Papapostolou (oblivious)

#include <stdio.h> /* printf */

#include "src/base/string.h"
#include "src/base/vector.h"
#include "src/scanner/Scanner.h"
#include "src/vm/on_demand_compilation_pipeline.h"

static string *SCAN(char *prompt) {
    return scanner_scan(prompt);
}

static void PRINT(MargValue evaluated) {
    printf("%s\n", string_get(marg_value_format(evaluated)));
}

static void PRINT_FORMAL(vector *formal_bytecode) {
    printf("[");
    size_t formal_bytecode_size = vector_size(formal_bytecode);
    if(formal_bytecode_size > 0) {
        for(size_t i = 0; i < formal_bytecode_size-1; i++)
            printf("%s, ", string_get(vector_get(formal_bytecode, i)));
        printf("%s", string_get(vector_get(formal_bytecode, formal_bytecode_size-1)));
    }
    printf("]\n");
}

static void margaret_repl(VM *vm) {
    while(1) {
        vector *formal_bytecode = FORMALIZE(READ(SCAN("$> ")));
        // PRINT_FORMAL(formal_bytecode);
        PRINT(EVAL(OPTIMIZE(EMIT(vm, formal_bytecode))));
    }
}

static void margaret_run_file(VM *vm, char *filename) {
    string *chars = LOAD(filename);
    TokenTable *tokens = READ(chars);
    vector *formal_bytecode = FORMALIZE(tokens);
    // PRINT_FORMAL(formal_bytecode);
    vm = EMIT(vm, formal_bytecode);
    vm = OPTIMIZE(vm);
    EVAL(vm);
}

static void banner(void) {
    printf("Usage: margaret <filename>\n");
}

int main(int argc, char **argv) {
    VM *vm = vm_new();
    if(argc < 2) {
        (void)argc;(void)argv;
        margaret_repl(vm);
    }
    else {
        margaret_run_file(vm, argv[1]);
    }
}
