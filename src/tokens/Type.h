#ifndef __TYPE_H_
#define __TYPE_H_

/**
 * @brief Token types definition.  Some of them are specific like int, float or
 * string while others like message/syntax symbol facilitate parsing for most of
 * Margaret's contstucts like array-type literals, procs, message sending and
 * solve grammar ambiguities.  Tokens should be specialized as singletons by
 * assigning different values for each token.
 */
typedef enum Type {
  TOKEN_EOF            = 0,
  TOKEN_NEWLINE        = 1,
  TOKEN_WHITESPACE     = 2,
  TOKEN_UNKNOWN        = 3,
  TOKEN_FLOAT          = 11,
  TOKEN_INTEGER        = 12,
  TOKEN_STRING         = 111,
  TOKEN_IDENTIFIER     = 201,
  TOKEN_INSTANCE       = 202,
  TOKEN_GLOBAL         = 203,
  TOKEN_MESSAGE_SYMBOL = 1001,
  TOKEN_SYNTAX_SYMBOL  = 1002
} Type;

#endif
