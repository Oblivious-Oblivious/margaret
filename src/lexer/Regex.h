#ifndef __REGEX_H_
#define __REGEX_H_

#include "../../libs/EmeraldsOniguruma/export/EmeraldsOniguruma.h"
#include "../tokens/Type.h"

typedef struct Regex {
  UChar *pattern;
  Type type;
} Regex;

static Regex REGEX_LIST[10] = {
  {
    .pattern = (UChar *)"^\\n",
    .type    = TOKEN_NEWLINE,
  },
  {
    .pattern = (UChar *)"^\\s+",
    .type    = TOKEN_WHITESPACE,
  },
  {
    .pattern = (UChar *)"^\\d+(_\\d+)*\\.\\d+(_\\d+)*",
    .type    = TOKEN_FLOAT,
  },
  {
    .pattern = (UChar *)"^\\b(?:0[bBoOxX][\\da-fA-F_]+|0|[1-9][\\d_]*)\\b",
    .type    = TOKEN_INTEGER,
  },
  {
    .pattern = (UChar *)"^@[a-zA-Z_][a-zA-Z0-9_]*",
    .type    = TOKEN_INSTANCE,
  },
  {
    .pattern = (UChar *)"^\\$[a-zA-Z_][a-zA-Z0-9_]*",
    .type    = TOKEN_GLOBAL,
  },
  {
    .pattern = (UChar *)"^[a-zA-Z_][a-zA-Z0-9_]*",
    .type    = TOKEN_IDENTIFIER,
  },
  {
    .pattern = (UChar *)"^[!?+\\-*\\\\/\\~<>=|&^;.`]+",
    .type    = TOKEN_MESSAGE_SYMBOL,
  },
  {
    .pattern = (UChar *)"^[()\\[\\]{},:#%]",
    .type    = TOKEN_SYNTAX_SYMBOL,
  },
  {
    .pattern = (UChar *)"^(['\"]).*?\\1",
    .type    = TOKEN_STRING,
  },
};

#endif
