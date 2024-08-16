#ifndef __PARSER_SPEC_H_
#define __PARSER_SPEC_H_

#include "../generic/_helpers.h"
#include "syntax/first_unit.module.spec.h"

module(ParserSpec, {
  it("traverses through the token table", {
    VM *vm     = vm_new("file.obl");
    vm->source = string_new("(42 factorial)");
    lexer_make_tokens(vm);
    assert_that_charptr(token_table_consume(vm)->value equals to "(");
    assert_that_charptr(token_table_consume(vm)->value equals to "42");
    assert_that_charptr(token_table_consume(vm)->value equals to "factorial");
    assert_that_charptr(token_table_consume(vm)->value equals to ")");
    assert_that_charptr(token_table_consume(vm)->value equals to "eof");
  });

  it("peeks on top of the token table", {
    VM *vm     = vm_new("file.obl");
    vm->source = string_new("(42 factorial)");
    lexer_make_tokens(vm);
    Token **tokens = vm->tokens;
    assert_that_charptr(tokens[1]->value equals to "42");
    assert_that_charptr(tokens[2]->value equals to "factorial");
    assert_that_charptr(tokens[0]->value equals to "(");
    assert_that_charptr(tokens[3]->value equals to ")");
    assert_that_charptr(tokens[4]->value equals to "eof");
  });

  first_unit();
})

#endif
