#ifndef __VERSION_SPEC_H_
#define __VERSION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "../src/version.h"

module(VersionSpec, {
  it("checks that latest version number", {
    assert_that_charptr(MARGARET_VERSION equals to "0.0.1");
  });

  it("checks that latest date", {
    assert_that_charptr(MARGARET_DATE equals to "2022-2024");
  });

  it("checks that latest link", {
    assert_that_charptr(MARGARET_LINK equals to "margaret.org");
  });
})

#endif
