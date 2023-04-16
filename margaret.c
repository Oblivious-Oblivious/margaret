// Copyright (C) 2023 Thanasis Papapostolou (Oblivious)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libs/boehm_gc/bdwgc/gc.h"
#include "libs/readline/readline/readline.h"
#include "libs/readline/readline/history.h"

#include "src/base/marg_string.h"
#include "src/base/marg_vector.h"
#include "src/evaluator/Evaluator.h"
#include "src/file_loader/FileLoader.h"
#include "src/lexer/Lexer.h"
#include "src/opcode/Chunk.h"
#include "src/parser/Parser.h"

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

static Chunk *EMIT(marg_vector *formal_messages_bytecode) {
    (void)formal_messages_bytecode;
    return chunk_new();
}

static Chunk *OPTIMIZE(Chunk *evaluated_bytecode) {
    return evaluated_bytecode;
}

static marg_string *EVAL(Chunk *bytecode) {
    (void)bytecode;
    return marg_string_new("0");
}

static void PRINT(marg_string *evaluated) {
    printf("%s\n", marg_string_get(evaluated));
}

static void PRINT_FORMAL(marg_vector *evaluated) {
    printf("[");
    size_t evaluated_size = marg_vector_size(evaluated);
    if(evaluated_size > 0) {
        for(size_t i = 0; i < evaluated_size-1; i++)
            printf("%s, ", marg_string_get(marg_vector_get(evaluated, i)));
        printf("%s", marg_string_get(marg_vector_get(evaluated, evaluated_size-1)));
    }
    printf("]\n");
}

static void margaret_repl(void) {
    // while(1) PRINT(EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(SCAN("$> ")))))));
    while(1) PRINT_FORMAL(FORMALIZE(READ(SCAN("$> "))));
}

static void margaret_run_file(char *filename) {
    marg_string *chars = file_loader_load(file_loader_new(), filename);
    Lexer *l = lexer_new(filename, chars);
    TokenTable *tokens = lexer_make_tokens(l);
    Parser *p = parser_new(tokens);
    marg_vector *formal_messages_bytecode = parser_analyze_syntax(p);

    size_t formal_messages_bytecode_size = marg_vector_size(formal_messages_bytecode);
    for(size_t i = 0; i < formal_messages_bytecode_size; i++)
        printf("%s\n", marg_string_get(marg_vector_get(formal_messages_bytecode, i)));
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
