#ifndef __VERSION_SPEC_H_
#define __VERSION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "../libs/EmeraldsOniguruma/export/EmeraldsOniguruma.h"
#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "../src/lexer/Lexer.h"
#include "../src/parser/Parser.h"
#include "../src/version.h"
#include "../src/vm/vm.h"

module(VersionSpec, {
  it("validates version number", {
    assert_that_charptr(MARGARET_VERSION equals to "0.0.1");
  });

  it("validates date", {
    assert_that_charptr(MARGARET_DATE equals to "2022-2024");
  });

  it("validates link", {
    assert_that_charptr(MARGARET_LINK equals to "margaret.org");
  });

  it("validates city", {
    assert_that_charptr(MARGARET_CITY equals to "Ioannina");
  });
})

#endif
