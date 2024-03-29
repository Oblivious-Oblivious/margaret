#include "Token.h"

#include "../base/memory.h"

Token *token_new(string *value, Type type, size_t line_number, char *filename) {
    Token *t = (Token*)collected_malloc(sizeof(Token));

    t->value = value;
    t->type = type;
    t->line_number = line_number;
    t->filename = filename;

    return t;
}

int token_equals_values(Token *tok, string *value) {
    return string_equals(tok->value, value);
}

int token_equals_objects(Token *tok1, Token *tok2) {
    if(string_equals(tok1->value, tok2->value))
        if(tok1->type == tok2->type)
            if(tok1->line_number == tok2->line_number)
                return tok1->filename == tok2->filename;

    return 0;
}
