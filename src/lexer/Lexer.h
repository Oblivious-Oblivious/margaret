#ifndef __LEXER_H_
#define __LEXER_H_

#include "../tokens/Token.h"
#include "../vm/vm.h"

/**
 * @brief Reports an error to stderrr
 * @param self -> The VM object
 * @param message -> The error message to report
 * @param lineno -> The line number of the token being lexed
 * @param charno -> The character number of the token being lexed
 * @return void* -> NULL
 */
void *lexer_error(VM *vm, const char *message, size_t lineno, size_t charno);

/**
 * @brief Tokenizes the next token from the source code
 * @param vm -> The VM object
 * @return Token* -> A token object
 */
Token *tokenize(VM *vm);

/**
 * @brief Tokenizes the input and stores into a token table
 * @param vm -> The VM object
 * @return VM* -> The VM object
 */
VM *lexer_make_tokens(VM *vm);

#endif
