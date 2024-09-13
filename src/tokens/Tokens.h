#ifndef __TOKENS_H_
#define __TOKENS_H_

#include "Type.h"

#include <stddef.h> /* size_t */

/**
 * @brief Describes a Token data structure that
    organizes lexing information from file inputs
 * @param values -> Vector or stringified token values
 * @param types -> Vector or token type annotations
 * @param linenos -> Vector of line numbers tokens were found on
 * @param charnos -> Vector of character numbers tokens were found on
 */
typedef struct Tokens {
  char **values;
  Type *types;
  size_t *linenos;
  size_t *charnos;
} Tokens;

/**
 * @brief Initializes a new token structure of arrays
 * @return Tokens* -> A new empty structure
 */
void tokens_init(Tokens *self);

/**
 * @brief Appends a new token to the structure of arrays
 * @param value -> A string value of the token consumed
 * @param type -> A type identifier for the token
 * @param lineno -> Line number this token was found on
 * @param charno -> Character number this token was found on
 * @return Token
 */
void tokens_add(
  Tokens *self, char *value, Type type, size_t lineno, size_t charno
);

/**
 * @brief Frees the all structure arrays
 * @param self -> The token structure
 */
void tokens_deinit(Tokens *self);

#endif
