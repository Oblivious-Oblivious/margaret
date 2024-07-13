#ifndef __SCALAR_MODULE_SPEC_H_
#define __SCALAR_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(scalar, {
  it("parses nil", { parse("$nil", vector_new(FM_NIL)); });

  it("parses false", { parse("$false", vector_new(FM_FALSE)); });

  it("parses true", { parse("$true", vector_new(FM_TRUE)); });

  it("parses labels", {
    parse("::ab", vector_new(FM_LABEL, string_new("ab")));
  });

  it("parses integers", {
    parse("0", vector_new(FM_INTEGER, string_new("0")));
    parse("1", vector_new(FM_INTEGER, string_new("1")));
    parse("2", vector_new(FM_INTEGER, string_new("2")));
    parse("42", vector_new(FM_INTEGER, string_new("42")));
    parse("4_200", vector_new(FM_INTEGER, string_new("4200")));
    parse(
      "9_223_372_036_854_775_807",
      vector_new(FM_INTEGER, string_new("9223372036854775807"))
    );
  });

  it("parses floats", {
    parse("0.0", vector_new(FM_FLOAT, string_new("0.0")));
    parse("1.0", vector_new(FM_FLOAT, string_new("1.0")));
    parse("2.0", vector_new(FM_FLOAT, string_new("2.0")));
    parse("42.0", vector_new(FM_FLOAT, string_new("42.0")));
    parse("4_200.0", vector_new(FM_FLOAT, string_new("4200.0")));
  });

  it("parses strings", {
    parse("\"hello\"", vector_new(FM_STRING, string_new("hello")));
    parse(
      "\"multi\nline\nstring\"",
      vector_new(FM_STRING, string_new("multi\nline\nstring"))
    );
  });

  it("parses identifiers", {
    parse("var1", vector_new(FM_LOCAL, string_new("var1")));
    parse("@var2", vector_new(FM_INSTANCE, string_new("@var2")));
    parse("$var3", vector_new(FM_GLOBAL, string_new("$var3")));
  });

  it("parses self and super", {
    parse("self", vector_new(FM_LOCAL, string_new("self")));
    parse("super", vector_new(FM_LOCAL, string_new("super")));
    parse("@self", vector_new(FM_SELF));
    parse("@super", vector_new(FM_SUPER));
  });
})

#endif
