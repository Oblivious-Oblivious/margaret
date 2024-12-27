#ifndef __SCALAR_MODULE_SPEC_H_
#define __SCALAR_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "variable.module.spec.h"

module(scalar, {
  it("parses labels", {
    parse(":ab", vector_new(FM_LABEL_LOCAL, string_new(":ab")));
    parse(":@ab", vector_new(FM_LABEL_INSTANCE, string_new(":@ab")));
    parse(":$ab", vector_new(FM_LABEL_GLOBAL, string_new(":$ab")));
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

  variable();
})

#endif
