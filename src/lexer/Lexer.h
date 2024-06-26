#ifndef __LEXER_H_
#define __LEXER_H_

#include "../tokens/Token.h"

/**
 * @brief Defines a lexer object
 * @param filename -> Current filename to lex tokens from
 * @param text -> string* version of scanned raw text
 * @param pos -> Current position in text array
 * @param lineno -> Counter for line numbers
 */
typedef struct Lexer {
  const char *filename;
  char *text;
  size_t lineno;
  size_t charno;
} Lexer;

/**
 * @brief Creates a new lexer object and initializes the loaded text
 * @param filename -> The filename of the file that we just loaded
 * @param text -> The text we read
 * @return Lexer*
 */
Lexer *lexer_new(const char *filename, char *text);

/**
 * @brief Reports an error to stderrr
 * @param self -> The lexer object
 * @param message -> The error message to report
 * @param token -> The token where the error occurred at
 * @return void* -> NULL
 */
void *lexer_error(Lexer *self, const char *message, char *token);

/**
 * @brief Tokenizes the input and stores into a token table
 * @param self -> The lexer object
 * @return Token** -> A table of Token objects;
 */
Token **lexer_make_tokens(Lexer *self);

#endif
