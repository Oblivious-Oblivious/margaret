#ifndef __STRING_SPEC_H_
#define __STRING_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/base/string.h"

module(string_spec, {
  describe("string", {
    it("creates a new string", {
      string *str = string_new("");
      assert_that(str isnot NULL);
    });

    it("creates a string with an initial char*", {
      string *str = string_new("initial");
      assert_that(str isnot NULL);
    });

    context("when a string pointer is not NULL", {
      it("returns the char* when calling `string_get`", {
        string *str = string_new("initial");
        assert_that(sizeof(string_get(str)) is sizeof(char *));
      });
    });

    context("when the initial value exitsts", {
      it("returns the correct char* when calling `string_get`", {
        string *str = string_new("initial");
        assert_that_charptr(string_get(str) equals to "initial");
      });
    });

    it("removes underscores from strings", {
      string *test = string_new("a_word_with_underscores");
      test         = string_remove_underscores(test);
      assert_that_charptr(string_get(test) equals to "awordwithunderscores");

      test = string_new("42_000_000");
      test = string_remove_underscores(test);
      assert_that_charptr(string_get(test) equals to "42000000");
    });
  });
})

#endif
