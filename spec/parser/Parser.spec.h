#ifndef __PARSER_SPEC_H_
#define __PARSER_SPEC_H_

#include "../generic/_helpers.h"
#include "syntax/first_unit.module.spec.h"

module(ParserSpec, {
  it("traverses through the token table", {
    Lexer *l     = lexer_new("file.obl", string_new("(42 factorial)"));
    Token **toks = lexer_make_tokens(l);
    assert_that_charptr(token_table_consume(toks)->value equals to "(");
    assert_that_charptr(token_table_consume(toks)->value equals to "42");
    assert_that_charptr(token_table_consume(toks)->value equals to "factorial");
    assert_that_charptr(token_table_consume(toks)->value equals to ")");
    assert_that_charptr(token_table_consume(toks)->value equals to "eof");
  });

  it("peeks on top of the token table", {
    Lexer *l       = lexer_new("file.obl", string_new("(42 factorial)"));
    Token **tokens = lexer_make_tokens(l);
    assert_that_charptr(tokens[1]->value equals to "42");
    assert_that_charptr(tokens[2]->value equals to "factorial");
    assert_that_charptr(tokens[0]->value equals to "(");
    assert_that_charptr(tokens[3]->value equals to ")");
    assert_that_charptr(tokens[4]->value equals to "eof");
  });

  first_unit();
})

#endif
