#ifndef __UNICODE_SPEC_H_
#define __UNICODE_SPEC_H_

#include "_helpers.h"

module(unicode_spec, {
  describe("reads unicode extended characters as identifiers", {
    it("parses local variables", {
      parse(
        "©© = 42",
        vector_new(
          FM_LOCAL,
          string_new("©©"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "☺☺ = 42",
        vector_new(
          FM_LOCAL,
          string_new("☺☺"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "😊😊 = 42",
        vector_new(
          FM_LOCAL,
          string_new("😊😊"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "¤¤ = 42",
        vector_new(
          FM_LOCAL,
          string_new("¤¤"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "ΩΩ = 42",
        vector_new(
          FM_LOCAL,
          string_new("ΩΩ"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "日日 = 42",
        vector_new(
          FM_LOCAL,
          string_new("日日"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "𠜎𠜎 = 42",
        vector_new(
          FM_LOCAL,
          string_new("𠜎𠜎"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "çç = 42",
        vector_new(
          FM_LOCAL,
          string_new("çç"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "🙂🙂 = 42",
        vector_new(
          FM_LOCAL,
          string_new("🙂🙂"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
      parse(
        "⚽⚽ = 42",
        vector_new(
          FM_LOCAL,
          string_new("⚽⚽"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
    });

    it("parses globals and instances", {
      parse(
        "@🙂🙂 = 42",
        vector_new(
          FM_INSTANCE,
          string_new("@🙂🙂"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );

      parse(
        "$🙂🙂 = 42",
        vector_new(
          FM_GLOBAL,
          string_new("$🙂🙂"),
          FM_INTEGER,
          string_new("42"),
          FM_BINARY,
          string_new("=")
        )
      );
    });

    it("parses unicode chars as strings", {
      parse(
        "\"Hello\", 'こんにちは_世界!', '世界𠜎🙂⚽日', '&', \"Ω¤😊©Aé世🍕\"",
        vector_new(
          FM_STRING,
          string_new("Hello"),
          FM_STRING,
          string_new("こんにちは_世界!"),
          FM_STRING,
          string_new("世界𠜎🙂⚽日"),
          FM_STRING,
          string_new("&"),
          FM_STRING,
          string_new("Ω¤😊©Aé世🍕")
        )
      );
    });
  });
})

#endif
