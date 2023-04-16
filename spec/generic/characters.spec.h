#ifndef __CHARACTERS_SPEC_H_
#define __CHARACTERS_SPEC_H_

#include "../_helpers.h"

module(characters_spec, {
    it("parses character literals", {
        parse("'a'", marg_vector_new(FM_CHAR, marg_string_new("a")));
        parse("'\n'", marg_vector_new(FM_CHAR, marg_string_new("\n")));
        parse("'œ'", marg_vector_new(FM_CHAR, marg_string_new("œ")));
    });

    it("parses character messages", {
        parse("(x = 'a' is_lowercase?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_lowercase?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' is_uppercase?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_uppercase?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' is_letter?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_letter?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' is_digit?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_digit?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' is_alphanumeric?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_alphanumeric?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' is_separator?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_separator?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' is_vowel?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_vowel?"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' to_digit)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("to_digit"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' to_lowercase)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("to_lowercase"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' to_uppercase)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("to_uppercase"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' to_ascii)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("to_ascii"), FM_STORE, marg_string_new("x")));
        parse("(x = 'a' <= 'b')", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_CHAR, marg_string_new("b"), FM_BINARY, marg_string_new("<="), FM_STORE, marg_string_new("x")));
    });
})

#endif
