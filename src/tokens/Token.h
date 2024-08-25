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
 * @param lineno -> Line number this token was found on
 * @param charno -> Character number this token was found on
 */
typedef struct Token {
  char *value;
  Type type;
  size_t lineno;
  size_t charno;
} Token;

/**
 * @brief Constructs a new token
 * @param value -> A string value of the token consumed
 * @param type -> A type identifier for the token
 * @param lineno -> Line number this token was found on
 * @param charno -> Character number this token was found on
 * @return Token
 */
Token *token_new(char *value, Type type, size_t lineno, size_t charno);

#endif
