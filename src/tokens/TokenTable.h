#ifndef __TOKEN_TABLE_H_
#define __TOKEN_TABLE_H_

#include "Token.h"

/**
 * @brief Consumes and removes the next token from the table
 * @param self -> The table to consume from
 * @return Token* -> The token consumed
 */
Token *token_table_consume(Token **self);

/**
 * @brief Consumes token by value
 * @param self -> The table to consume from
 * @param value -> The value expecting to consume
 * @param error_message -> An error message that prints in case of consumption
 * of wrong value
 * @return string* -> The found token
 */
char *token_table_ensure_value(
  Token **self, const char *value, const char *error_message
);

/**
 * @brief Consumes token by type
 * @param self -> The table to consume from
 * @param type -> The type expecting to consume
 * @param error_message -> An error message that prints in case of consumption
 * of wrong type
 * @return string*
 */
char *
token_table_ensure_type(Token **self, Type type, const char *error_message);

#endif
