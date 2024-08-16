#ifndef __REGEX_H_
#define __REGEX_H_

#include "../tokens/Type.h"

typedef struct Regex {
  const char *pattern;
  Type type;
} Regex;

static const Regex REGEX_LIST[] = {
  {
    .pattern = "^\\n",
    .type    = TOKEN_NEWLINE,
  },
  {
    .pattern = "^\\s+",
    .type    = TOKEN_WHITESPACE,
  },
  {
    .pattern = "^\\d+(_\\d+)*\\.\\d+(_\\d+)*",
    .type    = TOKEN_FLOAT,
  },
  {
    .pattern = "^(?:0[bBoOxX][\\da-fA-F_]+|0|[1-9][\\d_]*)",
    .type    = TOKEN_INTEGER,
  },
  {
    .pattern = "^@[a-zA-Z_][a-zA-Z0-9_]*",
    .type    = TOKEN_INSTANCE,
  },
  {
    .pattern = "^\\$[a-zA-Z_][a-zA-Z0-9_]*",
    .type    = TOKEN_GLOBAL,
  },
  {
    .pattern = "^[a-zA-Z_][a-zA-Z0-9_]*",
    .type    = TOKEN_IDENTIFIER,
  },
  {
    .pattern = "^[!?+\\-*\\\\/\\~<>=|&^;.`]+",
    .type    = TOKEN_MESSAGE_SYMBOL,
  },
  {
    .pattern = "^[()\\[\\]{},:#%]",
    .type    = TOKEN_SYNTAX_SYMBOL,
  },
  {
    .pattern = "^(['\"]).*?\\1",
    .type    = TOKEN_STRING,
  },
};

#endif
