#ifndef __REGEX_H_
#define __REGEX_H_

#include "../tokens/Type.h"

typedef struct Regex {
  const char *pattern;
  Type type;
} Regex;

static const Regex REGEX_LIST[] = {
  {
    "^\\n",
    TOKEN_NEWLINE,
  },
  {
    "^\\s+",
    TOKEN_WHITESPACE,
  },
  {
    "^\\d+(_\\d+)*\\.\\d+(_\\d+)*",
    TOKEN_FLOAT,
  },
  {
    "^(?:0[bBoOxX][\\da-fA-F_]+|0|[1-9][\\d_]*)",
    TOKEN_INTEGER,
  },
  {
    "^@[a-zA-Z_][a-zA-Z0-9_]*",
    TOKEN_INSTANCE,
  },
  {
    "^\\$[a-zA-Z_][a-zA-Z0-9_]*",
    TOKEN_GLOBAL,
  },
  {
    "^[a-zA-Z_][a-zA-Z0-9_]*",
    TOKEN_IDENTIFIER,
  },
  {
    "^[!?+\\-*\\\\/\\~<>=|&^;.`]+",
    TOKEN_MESSAGE_SYMBOL,
  },
  {
    "^[()\\[\\]{},:#%]",
    TOKEN_SYNTAX_SYMBOL,
  },
  {
    "^(['\"]).*?\\1",
    TOKEN_STRING,
  },
};

#endif
