// Copyright (C) 2023 Thanasis Papapostolou (Oblivious)

#include <stdio.h> /* printf */

#include "src/base/string.h"
#include "src/base/vector.h"
#include "src/emitter/Emitter.h"
#include "src/evaluator/Evaluator.h"
#include "src/inspector/Inspector.h"
#include "src/lexer/Lexer.h"
#include "src/loader/file_loader.h"
#include "src/optimizer/Optimizer.h"
#include "src/parser/Parser.h"
#include "src/scanner/Scanner.h"
#include "src/vm/vm.h"

static string *LOAD(char *filename) {
    return file_loader_load(file_loader_new(), filename);
}

static string *SCAN(char *prompt) {
    return scanner_scan(prompt);
}

static TokenTable *READ(string *chars) {
    return lexer_make_tokens(lexer_new("repl", chars));
}

static vector *FORMALIZE(TokenTable *tokens) {
    return parser_analyze_syntax(parser_new(tokens));
}

static VM *EMIT(VM *vm, vector *formal_bytecode) {
    return emitter_emit(vm, formal_bytecode);
}

static VM *OPTIMIZE(VM *vm) {
    return optimizer_optimize(vm);
}

static MargValue EVAL(VM *vm) {
    return evaluator_evaluate(vm);
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
