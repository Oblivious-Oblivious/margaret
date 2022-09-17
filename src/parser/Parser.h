#ifndef __PARSER_H_
#define __PARSER_H_

#include "../lexer/Lexer.h"
#include "../base/marg_string.h"

typedef struct Parser {
    TokenTable *table;
    // Bytecode *ast;
} Parser;

/**
 * @brief Constructs a new Parser object
 * @param tokens -> The list of tokens analyzed in the lexer
 * @return Parser* 
 */
Parser *parser_new(TokenTable *tokens);

#endif
