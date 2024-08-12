#ifndef __LEXER_H_
#define __LEXER_H_

#include "../tokens/Token.h"
#include "../vm/vm.h"

/**
 * @brief Reports an error to stderrr
 * @param self -> The VM object
 * @param message -> The error message to report
 * @param token -> The token where the error occurred at
 * @return void* -> NULL
 */
void *lexer_error(VM *vm, const char *message, char *token);

/**
 * @brief Tokenizes the input and stores into a token table
 * @param self -> The VM object
 * @param text -> The text we read
 * @return Token** -> A table of Token objects;
 */
Token **lexer_make_tokens(VM *vm, char *text);

#endif
