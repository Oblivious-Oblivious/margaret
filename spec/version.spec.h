#ifndef __VERSION_SPEC_H_
#define __VERSION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "../src/version.h"

module(VersionSpec, {
  it("checks that latest version number", {
    assert_that_charptr(MARGARET_VERSION equals to "0.0.1");
  });
})

#endif
