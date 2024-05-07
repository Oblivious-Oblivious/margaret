#ifndef __VERSION_SPEC_H_
#define __VERSION_SPEC_H_

#include "../src/version.h"
#include "cSpec.h"

module(VersionSpec, {
  it("checks that latest version number", {
    assert_that_charptr(MARGARET_VERSION equals to "0.0.1");
  });
})

#endif
