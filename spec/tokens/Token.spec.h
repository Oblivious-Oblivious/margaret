#ifndef __TOKEN_SPEC_H_
#define __TOKEN_SPEC_H_

#include "../../src/tokens/Token.h"
#include "../cSpec.h"

module(TokenSpec, {
    describe("Token", {
        it("has a type and a value", {
            Token *tok = token_new("42", TOKEN_INTEGER, 125);
            assert_that_charptr(tok->value equals to "42");
            assert_that_int(tok->type equals to TOKEN_INTEGER);
            assert_that_int(tok->line_number equals to 125);
        });

        it("has an equals message for values", {
            Token *tok = token_new("hello", TOKEN_STRING, 10);
            assert_that(token_equals_values(tok, "hello"));
        });

        it("has an equals message for values", {
            Token *tok1 = token_new("hello", TOKEN_STRING, 10);
            Token *tok2 = token_new("hello", TOKEN_STRING, 12);
            nassert_that(token_equals_objects(tok1, tok2));
        });
    });
})

#endif
