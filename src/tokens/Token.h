#ifndef __TOKEN_H_
#define __TOKEN_H_

#include <stdlib.h> /* size_t */
#include <string.h> /* strncmp, strlen */

#include "Type.h"

typedef struct Token {
    char *value;
    Type type;
    size_t line_number;
} Token;

/**
 * @brief Constructs a new token
 * @param value -> A string value of the token consumed
 * @param type -> A type identifier for the token
 * @param line_number -> The current line which the token was consumed at
 * @return Token
 */
Token *token_new(char *value, Type type, size_t line_number);

/**
 * @brief Checks for equality between a token and a string value
 * @param tok -> First token
 * @param value -> Second value
 * @return A boolean
 */
int token_equals_values(Token *tok, char *value);

/**
 * @brief Checks for equality between two tokens
 * @param tok1 -> First token
 * @param tok2 -> Second token
 * @return A boolean
 */
int token_equals_objects(Token *tok1, Token *tok2);

#endif
