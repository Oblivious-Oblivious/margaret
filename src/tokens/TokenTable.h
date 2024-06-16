#ifndef __TOKEN_TABLE_H_
#define __TOKEN_TABLE_H_

#include "Token.h"

/**
 * @brief Defines a token table (array-like) data structure.
    Allows for adding tokens, displaying values, retrieving
    lookaheads, as well as consuming by value or type.
 * @param token_list -> A vector storing tokens
 * @param pos -> Current position of table pointer
 */
typedef struct TokenTable {
  Token **token_list;
  size_t pos;
} TokenTable;

/**
 * @brief Displays the entirety or the table, prints all tokens
 * @param self -> The table to display
 */
void token_table_display(TokenTable *self);

/**
 * @brief Allocates and initializes a new token table.
 * @return TokenTable
 */
TokenTable *token_table_new(void);

/**
 * @brief Adds a new token to the table
 * @param self -> The table to add to
 * @param tok -> The created token to add
 */
void token_table_add(TokenTable *self, Token *tok);

/**
 * @brief Returns the number of elements in the table
 * @param self -> The table to count the size of
 * @return size_t Unsigned
 */
size_t token_table_size(TokenTable *self);

/**
 * @brief Gets an element from the list by index
 * @param self -> The table to get an element from
 * @param i -> The index of the element
 * @return Token* -> The found element
 */
Token *token_table_get(TokenTable *self, size_t i);

/**
 * @brief Looks ahead in the token table without consuming
 * @param self -> The table to look ahead from
 * @param i -> The number of tokens to walk ahead
 * @return Token* -> The found token
 */
Token *token_table_lookahead(TokenTable *self, size_t i);

/**
 * @brief Consumes the next token on the table without removing it
 * @param self -> The table to consume from
 * @return char* -> The token consumed
 */
Token *token_table_consume(TokenTable *self);

/**
 * @brief Consumes token by value
 * @param self -> The table to consume from
 * @param value -> The value expecting to consume
 * @param error_message -> An error message that prints in case of consumption
 * of wrong value
 * @return string* -> The found token
 */
char *token_table_ensure_value(
  TokenTable *self, const char *value, const char *error_message
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
token_table_ensure_type(TokenTable *self, Type type, const char *error_message);

#endif
