// Copyright (C) 2023 Thanasis Papapostolou (Oblivious)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static Chunk *EMIT(marg_vector *formal_bytecode) {
    return emitter_emit(emitter_new(formal_bytecode));
}

static Chunk *OPTIMIZE(Chunk *evaluated_bytecode) {
    return optimizer_optimize(optimizer_new(evaluated_bytecode));
}

static marg_string *EVAL(Chunk *bytecode) {
    return evaluator_evaluate(evaluator_new(bytecode));
}

static void PRINT(marg_string *evaluated) {
    printf("%s\n", marg_string_get(evaluated));
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
    Chunk *bytecode = EMIT(formal_bytecode);
    Chunk *optimized_bytecode = OPTIMIZE(bytecode);
    marg_string *evaluation_result = EVAL(optimized_bytecode);

    // inspect_chunk(bytecode);
    PRINT_FORMAL(formal_bytecode);

    (void)evaluation_result;
    // PRINT(evaluation_result);
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
