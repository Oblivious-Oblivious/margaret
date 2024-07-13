#ifndef __VARIABLE_MODULE_SPEC_H_
#define __VARIABLE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(variable, {
  it("parses nil", { parse("$nil", vector_new(FM_NIL)); });

  it("parses false", { parse("$false", vector_new(FM_FALSE)); });

  it("parses true", { parse("$true", vector_new(FM_TRUE)); });

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
