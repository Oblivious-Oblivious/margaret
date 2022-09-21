#include "Token.h"

Token *token_new(marg_string *value, Type type, size_t line_number) {
    Token *t = (Token*)malloc(sizeof(Token));

    t->value = value;
    t->type = type;
    t->line_number = line_number;

    return t;
}

int token_equals_values(Token *tok, marg_string *value) {
    return marg_string_equals(tok->value, value);
}

int token_equals_objects(Token *tok1, Token *tok2) {
    if(marg_string_equals(tok1->value, tok2->value))
        if(tok1->type == tok2->type)
            return tok1->line_number == tok2->line_number;

    return 0;
}
