#ifndef __VARIABLES_SPEC_H_
#define __VARIABLES_SPEC_H_

#include "_helpers.h"

module(variables_spec, {
  it("parses local variables", {
    parse("x", vector_new(FM_LOCAL, string_new("x"), FM_POP));
    parse("y", vector_new(FM_LOCAL, string_new("y"), FM_POP));
    parse(
      "(x, y)",
      vector_new(
        FM_LOCAL, string_new("x"), FM_POP, FM_LOCAL, string_new("y"), FM_POP
      )
    );
  });

  it("parses instance variables", {
    parse("@x", vector_new(FM_INSTANCE, string_new("@x"), FM_POP));
    parse("@y", vector_new(FM_INSTANCE, string_new("@y"), FM_POP));
    parse(
      "(@x, @y, z)",
      vector_new(
        FM_INSTANCE,
        string_new("@x"),
        FM_POP,
        FM_INSTANCE,
        string_new("@y"),
        FM_POP,
        FM_LOCAL,
        string_new("z"),
        FM_POP
      )
    );
  });

  it("parses global variables", {
    parse("$x", vector_new(FM_GLOBAL, string_new("$x"), FM_POP));
    parse("$y", vector_new(FM_GLOBAL, string_new("$y"), FM_POP));
    parse(
      "($x, @y, z)",
      vector_new(
        FM_GLOBAL,
        string_new("$x"),
        FM_POP,
        FM_INSTANCE,
        string_new("@y"),
        FM_POP,
        FM_LOCAL,
        string_new("z"),
        FM_POP
      )
    );
  });
})

#endif
