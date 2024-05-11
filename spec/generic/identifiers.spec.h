#ifndef __IDENTIFIERS_SPEC_H_
#define __IDENTIFIERS_SPEC_H_

#include "_helpers.h"

module(identifiers_spec, {
  it("parses identifiers", {
    parse(
      "(ident, 42, another)",
      vector_new(
        FM_LOCAL,
        string_new("ident"),
        FM_POP,
        FM_INTEGER,
        string_new("42"),
        FM_POP,
        FM_LOCAL,
        string_new("another"),
        FM_POP
      )
    );
    parse(
      "(stuff,ident2)",
      vector_new(
        FM_LOCAL,
        string_new("stuff"),
        FM_POP,
        FM_LOCAL,
        string_new("ident2"),
        FM_POP
      )
    );
  });

  it("parses normal and instance variables", {
    parse("variable", vector_new(FM_LOCAL, string_new("variable"), FM_POP));
    parse("@instvar", vector_new(FM_INSTANCE, string_new("@instvar"), FM_POP));
    parse("@x", vector_new(FM_INSTANCE, string_new("@x"), FM_POP));
  });

  it("parses pseudo variables (used as normal identifiers)", {
    parse("$nil", vector_new(FM_NIL, FM_POP));
    parse("$true", vector_new(FM_TRUE, FM_POP));
    parse("$false", vector_new(FM_FALSE, FM_POP));
    parse("@self", vector_new(FM_SELF, FM_POP));
    parse("@super", vector_new(FM_SUPER, FM_POP));
  });
})

#endif
