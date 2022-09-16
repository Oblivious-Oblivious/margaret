#include "Lexer.h"

#include <stdio.h> /* fprintf */
#include <ctype.h> /* tolower */

#include "../tokens/Type.h"

Lexer *lexer_new(char *filename, marg_string *text) {
    Lexer *self = (Lexer*)malloc(sizeof(Lexer));

    self->filename = filename;
    self->text = text;
    self->pos = -1;
    self->lineno = 1;

    return self;
}

void *lexer_error(Lexer *self, char *message) {
    fprintf(stderr, "%s:%llu: \033[1;31merror:\033[0m %s\n", self->filename, self->lineno, message);
    return NULL;
}

char lexer_next_character(Lexer *self) {
    self->pos++;
    return marg_string_get_char_at_index(self->text, self->pos);
}

char lexer_peek_character(Lexer *self, size_t i) {
    return marg_string_get_char_at_index(self->text, self->pos + i);
}

static Token *lexer_tokenize_integer(Lexer *self, char c) {
    marg_string *final_number = marg_string_new("");
    while(1) {
        marg_string_add_char(final_number, c);
        c = lexer_peek_character(self, 1);
        if(c == '_') {
            c = lexer_next_character(self);
            continue;
        }

        if(c == '\0' || !regex_matches(c, REGEX_NUMBER))
            break;
        
        c = lexer_next_character(self);
    }

    return token_new(marg_string_get(final_number), TOKEN_INTEGER, self->lineno);
}

static Token *lexer_tokenize_number_special(Lexer *self, marg_string *final_number, const char *matcher, Type type) {
    // Fraction part
    char c = lexer_next_character(self);
    marg_string_add_char(final_number, tolower(c));

    // Rest of number
    c = lexer_next_character(self);
    while(1) {
        marg_string_add_char(final_number, tolower(c));
        c = lexer_peek_character(self, 1);
        if(c == '_') {
            c = lexer_next_character(self);
            continue;
        }

        if(c == '\0' || !regex_matches(c, matcher))
            break;
        
        c = lexer_next_character(self);
    }

    return token_new(marg_string_get(final_number), type, self->lineno);
}

static Token *lexer_tokenize_integer_or_float(Lexer *self, char c) {
    Token *int_token = lexer_tokenize_integer(self, c);

    c = lexer_peek_character(self, 1);
    if(c == '.')
        return lexer_tokenize_number_special(self, marg_string_new(int_token->value), REGEX_NUMBER, TOKEN_FLOAT);
    else
        return int_token;
}

static Token *lexer_tokenize_number(Lexer *self, char c) {
    marg_string *final_number = marg_string_new("");
    marg_string_add_char(final_number, c);

    if(c == '0') {
        c = lexer_peek_character(self, 1);
        if(c == '.')
            return lexer_tokenize_number_special(self, final_number, REGEX_NUMBER, TOKEN_FLOAT);
        else if(c == 'b' || c == 'B')
            return lexer_tokenize_number_special(self, final_number, REGEX_BINARY, TOKEN_INTEGER);
        else if(c == 'x' || c == 'X')
            return lexer_tokenize_number_special(self, final_number, REGEX_HEXADECIMAL, TOKEN_INTEGER);
        else if(c == 'o' || c == 'O')
            return lexer_tokenize_number_special(self, final_number, REGEX_OCTAL, TOKEN_INTEGER);
        else
            return token_new("0", TOKEN_INTEGER, self->lineno);
    }
    else {
        return lexer_tokenize_integer_or_float(self, c);
    }
}

static Token *lexer_tokenize_identifier(Lexer *self, char c) {
    marg_string *final_identifier = marg_string_new("");

    // TODO Add unicode support for identifier names (APL or Julia style)
    while(1) {
        marg_string_add_char(final_identifier, c);
        c = lexer_peek_character(self, 1);
        if(c == '\0' || !(regex_matches(c, REGEX_NUMBER) || c == '_' || regex_matches(c, REGEX_LETTER)))
            break;
        c = lexer_next_character(self);
    }

    return token_new(marg_string_get(final_identifier), TOKEN_IDENTIFIER, self->lineno);
}

static Token *lexer_tokenize_message_symbol(Lexer *self, char c) {
    marg_string *final_symbol = marg_string_new("");

    while(1) {
        marg_string_add_char(final_symbol, c);
        c = lexer_peek_character(self, 1);
        if(c == '\0' || !(regex_matches(c, REGEX_MESSAGE_SYMBOL)))
            break;
        c = lexer_next_character(self);
    }

    char maybe_id_symb = marg_string_get_char_at_index(final_symbol, 0);
    if(marg_string_size(final_symbol) == 1 || regex_matches(maybe_id_symb, REGEX_ID_SYMBOL))
        return token_new(marg_string_get(final_symbol), TOKEN_ID_SYMBOL, self->lineno);
    else
        return token_new(marg_string_get(final_symbol), TOKEN_MESSAGE_SYMBOL, self->lineno);
}

static Token *lexer_tokenize_character(Lexer *self, char c) {
    marg_string *final_char = marg_string_new("");
    marg_string_add_char(final_char, c);
    c = lexer_next_character(self);
    if(!regex_matches(c, REGEX_SINGLE_QUOTE)) {
        marg_string_add_char(final_char, c);
        c = lexer_next_character(self);
        if(c == '\0')
            return lexer_error(self, "unterminated character literal");
    }
    marg_string_add_char(final_char, c);
    return token_new(marg_string_get(final_char), TOKEN_CHAR, self->lineno);
}

static Token *lexer_tokenize_string(Lexer *self, char c) {
    marg_string *final_string = marg_string_new("");
    marg_string_add_char(final_string, c);
    c = lexer_next_character(self);
    while(!regex_matches(c, REGEX_DOUBLE_QUOTE)) {
        marg_string_add_char(final_string, c);
        c = lexer_next_character(self);
        if(c == '\0')
            return lexer_error(self, "unterminated string literal");
        else if(regex_matches(c, REGEX_NEWLINE))
            self->lineno++;
    }
    marg_string_add_char(final_string, c);
    return token_new(marg_string_get(final_string), TOKEN_STRING, self->lineno);
}

TokenTable *lexer_make_tokens(Lexer *self) {
    TokenTable *token_table = token_table_new();

    char c;
    while(1) {
        c = lexer_next_character(self);
        if(c == '\0')
            break;
        else if(regex_matches(c, REGEX_NEWLINE))
            self->lineno++;
        else if(regex_matches(c, REGEX_WHITESPACE))
            ; // Skip
        else if(regex_matches(c, REGEX_NUMBER))
            token_table_add(token_table, lexer_tokenize_number(self, c));
        else if(regex_matches(c, REGEX_LETTER) || c == '_')
            token_table_add(token_table, lexer_tokenize_identifier(self, c));
        else if(regex_matches(c, REGEX_MESSAGE_SYMBOL))
            token_table_add(token_table, lexer_tokenize_message_symbol(self, c));
        else if(regex_matches(c, REGEX_SYNTAX_SYMBOL)) {
            marg_string *symb = marg_string_new("");
            marg_string_add_char(symb, c);
            token_table_add(token_table, token_new(marg_string_get(symb), TOKEN_SYNTAX_SYMBOL, self->lineno));
        }
        else if(regex_matches(c, REGEX_SINGLE_QUOTE)) {
            Token *tok = lexer_tokenize_character(self, c);
            if(tok == NULL)
                break;
            token_table_add(token_table, tok);
        }
        else if(regex_matches(c, REGEX_DOUBLE_QUOTE)) {
            Token *tok = lexer_tokenize_string(self, c);
            if(tok == NULL)
                break;
            token_table_add(token_table, tok);
        }
        else {
            lexer_error(self, "Unexpected character.");
            break;
        }
    }

    token_table_add(token_table, token_new("eof", TOKEN_EOF, self->lineno));

    return token_table;
}
