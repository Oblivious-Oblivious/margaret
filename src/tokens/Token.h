#ifndef __TOKEN_H_
#define __TOKEN_H_

#include <stdlib.h> /* size_t */
#include <string.h> /* strncmp, strlen */

#include "Type.h"

#include "../base/string.h"

/**
 * @brief Describes a Token data structure that
    organizes lexing information from file inputs
 * @param value -> Stringified value of the token
 * @param type -> A token type annotation
 * @param line_number -> Current line number this token was found on
 * @param filename -> Filename this token was found on
 */
typedef struct Token {
    string *value;
    Type type;
    size_t line_number;
    const char *filename;
} Token;

/**
 * @brief Constructs a new token
 * @param value -> A string value of the token consumed
 * @param type -> A type identifier for the token
 * @param line_number -> The current line which the token was consumed at
 * @param filename -> The current line which the token was consumed at
 * @return Token
 */
Token *token_new(string *value, Type type, size_t line_number, const char *filename);

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
