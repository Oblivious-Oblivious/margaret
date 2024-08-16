#ifndef __TOKEN_H_
#define __TOKEN_H_

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h"
#include "Type.h"

#include <stdlib.h>

/**
 * @brief Describes a Token data structure that
    organizes lexing information from file inputs
 * @param value -> Stringified value of the token
 * @param type -> A token type annotation
 * @param filename -> Filename this token was found on
 */
typedef struct Token {
  char *value;
  Type type;
} Token;

/**
 * @brief Constructs a new token
 * @param value -> A string value of the token consumed
 * @param type -> A type identifier for the token
 * @param filename -> The current line which the token was consumed at
 * @return Token
 */
Token *token_new(char *value, Type type);

/**
 * @brief Checks for equality between a token and a string value
 * @param tok -> First token
 * @param value -> Second value
 * @return A boolean
 */
bool token_equals_values(Token *tok, char *value);

#endif
