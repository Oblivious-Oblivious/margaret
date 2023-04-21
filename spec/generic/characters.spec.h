#ifndef __CHARACTERS_SPEC_H_
#define __CHARACTERS_SPEC_H_

#include "../_helpers.h"

module(characters_spec, {
    it("parses character literals", {
        parse("'a'", vector_new(FM_CHAR, string_new("a")));
        parse("'\n'", vector_new(FM_CHAR, string_new("\n")));
        parse("'œ'", vector_new(FM_CHAR, string_new("œ")));
    });

    it("parses character messages", {
        parse("(x = 'a' is_lowercase?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_lowercase?"), FM_STORE, string_new("x")));
        parse("(x = 'a' is_uppercase?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_uppercase?"), FM_STORE, string_new("x")));
        parse("(x = 'a' is_letter?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_letter?"), FM_STORE, string_new("x")));
        parse("(x = 'a' is_digit?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_digit?"), FM_STORE, string_new("x")));
        parse("(x = 'a' is_alphanumeric?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_alphanumeric?"), FM_STORE, string_new("x")));
        parse("(x = 'a' is_separator?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_separator?"), FM_STORE, string_new("x")));
        parse("(x = 'a' is_vowel?)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("is_vowel?"), FM_STORE, string_new("x")));
        parse("(x = 'a' to_digit)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("to_digit"), FM_STORE, string_new("x")));
        parse("(x = 'a' to_lowercase)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("to_lowercase"), FM_STORE, string_new("x")));
        parse("(x = 'a' to_uppercase)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("to_uppercase"), FM_STORE, string_new("x")));
        parse("(x = 'a' to_ascii)", vector_new(FM_CHAR, string_new("a"), FM_UNARY, string_new("to_ascii"), FM_STORE, string_new("x")));
        parse("(x = 'a' <= 'b')", vector_new(FM_CHAR, string_new("a"), FM_CHAR, string_new("b"), FM_BINARY, string_new("<="), FM_STORE, string_new("x")));
    });
})

#endif
