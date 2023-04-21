// Copyright (C) 2023 Thanasis Papapostolou (Oblivious)

#include <stdio.h>

#include "libs/boehm_gc/bdwgc/gc.h"
#include "libs/readline/readline/readline.h"
#include "libs/readline/readline/history.h"

#include "src/base/file_loader.h"
#include "src/base/marg_string.h"
#include "src/base/marg_vector.h"
#include "src/emitter/Emitter.h"
#include "src/evaluator/Evaluator.h"
#include "src/inspector/Inspector.h"
#include "src/lexer/Lexer.h"
#include "src/optimizer/Optimizer.h"
#include "src/parser/Parser.h"

static marg_string *LOAD(char *filename) {
    return file_loader_load(file_loader_new(), filename);
}

static marg_string *SCAN(char *prompt) {
    char *line = readline(prompt);
    if(!strcmp(line, ""))
        return marg_string_new("()");
    else if(!strcmp(line, "<<exit>>") || !strcmp(line, "<<quit>>"))
        exit(0);
    else {
        add_history(line);
        return marg_string_new(line);
    }
}

static TokenTable *READ(marg_string *chars) {
    return lexer_make_tokens(lexer_new("repl", chars));
}

static marg_vector *FORMALIZE(TokenTable *tokens) {
    return parser_analyze_syntax(parser_new(tokens));
}

static VM *EMIT(marg_vector *formal_bytecode) {
    return emitter_emit(formal_bytecode);
}

static VM *OPTIMIZE(VM *vm) {
    return optimizer_optimize(vm);
}

static MargValue EVAL(VM *vm) {
    return evaluator_evaluate(vm);
}

static void PRINT(MargValue evaluated) {
    printf("%s\n", marg_string_get(marg_value_format(evaluated)));
}

static void PRINT_FORMAL(marg_vector *formal_bytecode) {
    printf("[");
    size_t formal_bytecode_size = marg_vector_size(formal_bytecode);
    if(formal_bytecode_size > 0) {
        for(size_t i = 0; i < formal_bytecode_size-1; i++)
            printf("%s, ", marg_string_get(marg_vector_get(formal_bytecode, i)));
        printf("%s", marg_string_get(marg_vector_get(formal_bytecode, formal_bytecode_size-1)));
    }
    printf("]\n");
}

static void margaret_repl(void) {
    // while(1) PRINT(EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(SCAN("$> ")))))));
    while(1) PRINT_FORMAL(FORMALIZE(READ(SCAN("$> "))));
}

static void margaret_run_file(char *filename) {
    marg_string *chars = LOAD(filename);
    TokenTable *tokens = READ(chars);
    marg_vector *formal_bytecode = FORMALIZE(tokens);
    PRINT_FORMAL(formal_bytecode);
    VM *vm = EMIT(formal_bytecode);

    vm = OPTIMIZE(vm);

    MargValue evaluation_result = EVAL(vm);
    PRINT(evaluation_result);

    inspect_and_print_vm_bytecode(vm);
}

static void banner(void) {
    printf("Usage: margaret <filename>\n");
}

int main(int argc, char **argv) {
    GC_INIT();

    if(argc < 2) {
        (void)argc;(void)argv;
        margaret_repl();
    }
    else {
        margaret_run_file(argv[1]);
    }
}
