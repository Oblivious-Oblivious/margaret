#ifndef __ALTERNATE_TO_DEC_SPEC_H_
#define __ALTERNATE_TO_DEC_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/lexer/alternate_to_dec.h"

module(alternate_to_dec_spec, {
  it("tries to convert NULL strings", {
    char *bin = string_new(NULL);
    bin_to_dec(bin);
    assert_that(bin is NULL);

    char *oct = string_new(NULL);
    oct_to_dec(oct);
    assert_that(oct is NULL);

    char *hex = string_new(NULL);
    hex_to_dec(hex);
    assert_that(hex is NULL);
  });

  it("converts from binary to decimal", {
    char *bin = string_new("101010");
    bin_to_dec(bin);
    assert_that_charptr(bin equals to "42");
  });

  it("converts from octal to decimal", {
    char *oct = string_new("12345");
    oct_to_dec(oct);
    assert_that_charptr(oct equals to "5349");
  });

  it("converts from hexadecimal to decimal", {
    char *hex = string_new("bEeF");
    hex_to_dec(hex);
    assert_that_charptr(hex equals to "48879");
  });
})

#endif
