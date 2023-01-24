// Copyright (C) 2023 Thanasis Papapostolou (Oblivious)
// See end of file for copyright information
// This file is part of margaret.

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

static marg_vector *EVAL(TokenTable *tokens) {
    return parser_analyze_syntax(parser_new(tokens));
}

static void PRINT(marg_vector *evaluated) {
    printf("[");
    size_t evaluated_size = marg_vector_size(evaluated);
    if(evaluated_size > 0) {
        for(size_t i = 0; i < evaluated_size-1; i++)
            printf("%s, ", marg_string_get(marg_vector_get(evaluated, i)));
        printf("%s", marg_string_get(marg_vector_get(evaluated, evaluated_size-1)));
    }
    printf("]\n");
}

void margaret_repl(void) {
    while(1) PRINT(EVAL(READ(SCAN("$> "))));
}

marg_string *margaret_run_file(char *filename) {
    marg_string *chars = file_loader_load(file_loader_new(), filename);
    Lexer *l = lexer_new(filename, chars);
    TokenTable *tokens = lexer_make_tokens(l);
    Parser *p = parser_new(tokens);
    marg_vector *bytecode = parser_analyze_syntax(p);
    Evaluator *e = evaluator_new(bytecode);
    marg_string *evaluated = evaluator_evaluate(e);

    size_t bytecode_size = marg_vector_size(bytecode);
    for(size_t i = 0; i < bytecode_size; i++)
        printf("%s\n", marg_string_get(marg_vector_get(bytecode, i)));
    
    return evaluated;
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

// Copyright (C) 2023 Thanasis Papapostolou (Oblivious)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
