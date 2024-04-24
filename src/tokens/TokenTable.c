#include "TokenTable.h"

#include <stdio.h> /* fprintf */

#include "../base/memory.h"

/**
 * @brief
    TODO Abstract error somewhere closer to boundary
    TODO Name error messages or abstract to macros
 * @param token -> The token where the error occured at
 * @param message -> The message to display
 * @return string* -> NULL pointer
 */
static string *error(Token *token, const char *message) {
    fprintf(stderr, "%s:%zu: \033[1;31merror:\033[0m %s  Token: \033[1;31m`%s`\033[0m\n", token->filename, token->line_number, message, string_get(token->value));
    return NULL;
}

void token_table_display(TokenTable *self) {
    for(size_t i = 0; i < token_table_size(self); i++) {
        Token *t = token_table_get(self, i);
        printf("(%s,%d,%zu)\n", string_get(t->value), t->type, t->line_number);
    }
    printf("\n");
}

TokenTable *token_table_new(void) {
    TokenTable *t = (TokenTable*)collected_malloc(sizeof(TokenTable));

    t->token_list = vector_new_empty();
    t->pos = 0;

    return t;
}

void token_table_add(TokenTable *self, Token *tok) {
    vector_add(self->token_list, tok);
}

size_t token_table_size(TokenTable *self) {
    return vector_size(self->token_list);
}

Token *token_table_get(TokenTable *self, size_t i) {
    size_t size = token_table_size(self);
    if(i >= size)
        return vector_get(self->token_list, size - 1);
    else
        return vector_get(self->token_list, i);
}

Token *token_table_lookahead(TokenTable *self, size_t i) {
    return token_table_get(self, self->pos + i - 1);
}

Token *token_table_consume(TokenTable *self) {
    self->pos += 1;
    return token_table_get(self, self->pos - 1);
}

string *token_table_ensure_value(TokenTable *self, const char *value, const char *error_message) {
    Token *token = token_table_consume(self);
    if(token_equals_values(token, string_new(value)))
        return token->value;
    else
        return error(token, error_message);
}

string *token_table_ensure_type(TokenTable *self, Type type, const char *error_message) {
    Token *token = token_table_consume(self);
    if(token->type == type)
        return token->value;
    else
        return error(token, error_message);
}
