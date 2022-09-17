#ifndef __PARSER_SPEC_H_
#define __PARSER_SPEC_H_

#include "../../src/parser/Parser.h"
#include "../cSpec.h"

module(ParserSpec, {
    describe("Parser", {
        it("creates a Parser object with Lexer as a parameter", {
            Lexer *l = lexer_new("file.obl", marg_string_new("(42 factorial)"));
            TokenTable *tokens = lexer_make_tokens(l);
            Parser *p = parser_new(tokens);
            assert_that(p isnot NULL);
        });

        it("traverses through the token table", {
            Lexer *l = lexer_new("file.obl", marg_string_new("(42 factorial)"));
            TokenTable *tokens = lexer_make_tokens(l);
            Parser *p = parser_new(tokens);
            assert_that_charptr(token_table_consume(p->table)->value equals to "(");
            assert_that_charptr(token_table_consume(p->table)->value equals to "42");
            assert_that_charptr(token_table_consume(p->table)->value equals to "factorial");
            assert_that_charptr(token_table_consume(p->table)->value equals to ")");
            assert_that_charptr(token_table_consume(p->table)->value equals to "eof");
        });

        it("peeks on top of the token table", {
            Lexer *l = lexer_new("file.obl", marg_string_new("(42 factorial)"));
            TokenTable *tokens = lexer_make_tokens(l);
            Parser *p = parser_new(tokens);
            assert_that_charptr(token_table_lookahead(p->table, 5)->value equals to "eof");
            assert_that_charptr(token_table_lookahead(p->table, 2)->value equals to "42");
            assert_that_charptr(token_table_lookahead(p->table, 3)->value equals to "factorial");
            assert_that_charptr(token_table_lookahead(p->table, 1)->value equals to "(");
            assert_that_charptr(token_table_lookahead(p->table, 4)->value equals to ")");
        });
    });
})

#endif
