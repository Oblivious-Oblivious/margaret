#ifndef __TOKEN_SPEC_H_
#define __TOKEN_SPEC_H_

#include "../../src/tokens/Token.h"
#include "../cSpec.h"

module(TokenSpec, {
    it("has a type and a value", {
        Token *tok = token_new(marg_string_new("42"), TOKEN_INTEGER, 125, "file1.marg");
        assert_that_charptr(marg_string_get(tok->value) equals to "42");
        assert_that_int(tok->type equals to TOKEN_INTEGER);
        assert_that_int(tok->line_number equals to 125);
        assert_that_charptr(tok->filename equals to "file1.marg");
    });

    it("has an equals message for values", {
        Token *tok = token_new(marg_string_new("hello"), TOKEN_STRING, 10, "file2.marg");
        assert_that(token_equals_values(tok, marg_string_new("hello")));
    });

    it("has an equals message for values", {
        Token *tok1 = token_new(marg_string_new("hello"), TOKEN_STRING, 10, "file3.marg");
        Token *tok2 = token_new(marg_string_new("hello"), TOKEN_STRING, 12, "file3.marg");
        nassert_that(token_equals_objects(tok1, tok2));
    });
})

#endif
