#ifndef __TOKEN_TABLE_H_
#define __TOKEN_TABLE_H_

#include "../vm/vm.h"
#include "Token.h"

/**
 * @brief Consumes and removes the next token from the table
 * @param vm -> The vm containing the token table
 * @return Token* -> The token consumed
 */
Token *token_table_consume(VM *vm);

/**
 * @brief Consumes token by value
 * @param vm -> The vm containing the token table
 * @param value -> The value expecting to consume
 * @param error_message -> An error message that prints in case of consumption
 * of wrong value
 * @return string* -> The found token
 */
char *
token_table_ensure_value(VM *vm, const char *value, const char *error_message);

/**
 * @brief Consumes token by type
 * @param vm -> The vm containing the token table
 * @param type -> The type expecting to consume
 * @param error_message -> An error message that prints in case of consumption
 * of wrong type
 * @return string*
 */
char *token_table_ensure_type(VM *vm, Type type, const char *error_message);

#endif
