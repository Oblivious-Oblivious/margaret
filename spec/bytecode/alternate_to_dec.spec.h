#ifndef __ALTERNATE_TO_DEC_SPEC_H_
#define __ALTERNATE_TO_DEC_SPEC_H_

#include "../../src/bytecode/alternate_to_dec.h"
#include "../cSpec.h"

module(alternate_to_dec_spec, {
  it("converts from binary to decimal", {
    char *bin = bin_to_dec("101010");
    assert_that_charptr(bin equals to "42");
  });

  it("converts from octal to decimal", {
    char *oct = oct_to_dec("12345");
    assert_that_charptr(oct equals to "5349");
  });

  it("converts from hexadecimal to decimal", {
    char *hex = hex_to_dec("bEeF");
    assert_that_charptr(hex equals to "48879");
  });
})

#endif
