#ifndef __TOKEN_H_
#define __TOKEN_H_

#include <stdlib.h> /* size_t */
#include <string.h> /* strncmp, strlen */

#include "Type.h"

#include "../base/string.h"

typedef struct Token {
    string *value;
    Type type;
    size_t line_number;
    char *filename;
} Token;

/**
 * @brief Constructs a new token
 * @param value -> A string value of the token consumed
 * @param type -> A type identifier for the token
 * @param line_number -> The current line which the token was consumed at
 * @param filename -> The current line which the token was consumed at
 * @return Token
 */
Token *token_new(string *value, Type type, size_t line_number, char *filename);

/**
 * @brief Checks for equality between a token and a string value
 * @param tok -> First token
 * @param value -> Second value
 * @return A boolean
 */
int token_equals_values(Token *tok, string *value);

/**
 * @brief Checks for equality between two tokens
 * @param tok1 -> First token
 * @param tok2 -> Second token
 * @return A boolean
 */
int token_equals_objects(Token *tok1, Token *tok2);

#endif
