#include "TokenTable.h"

#include <stdio.h> /* printf */

/**
 * @brief
    TODO Abstract error somewhere closer to boundary
    TODO Track line numbers to each error
    TODO Gather a list of errors and output after parsing all code
 * @param message -> The message to display
 * @return marg_string* -> NULL pointer
 */
static marg_string *error(char *message) {
    printf("%s\n", message);
    exit(1);
    return NULL;
}

TokenTable *token_table_new(void) {
    TokenTable *t = (TokenTable*)malloc(sizeof(TokenTable));

    t->token_list = marg_vector_new();
    t->pos = -1;

    return t;
}

void token_table_add(TokenTable *self, Token *tok) {
    marg_vector_add(self->token_list, tok);
}

size_t token_table_size(TokenTable *self) {
    return marg_vector_size(self->token_list);
}

Token *token_table_get(TokenTable *self, size_t i) {
    size_t size = token_table_size(self);
    if(i >= size)
        return marg_vector_get(self->token_list, size - 1);
    else
        return marg_vector_get(self->token_list, i);
}

Token *token_table_lookahead(TokenTable *self, size_t i) {
    return token_table_get(self, self->pos + i);
}

Token *token_table_consume(TokenTable *self) {
    self->pos += 1;
    return token_table_get(self, self->pos);
}

marg_string *token_table_ensure_value(TokenTable *self, char *value, char *error_message) {
    Token *token = token_table_consume(self);
    if(token_equals_values(token, marg_string_new(value)))
        return token->value;
    else
        return error(error_message);
}

marg_string *token_table_ensure_type(TokenTable *self, Type type, char *error_message) {
    Token *token = token_table_consume(self);
    if(token->type == type)
        return token->value;
    else
        return error(error_message);
}
