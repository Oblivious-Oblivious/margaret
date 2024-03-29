#ifndef __TYPE_H_
#define __TYPE_H_

/**
 * @brief Token types definition
    Some of them are specific like int, float or string
    while others like message/syntax symbol facilitate
    parsing for most of Margaret's contstucts like array-
    type literals, procs, message sending and solve grammar
    ambiguities.  Tokens should be specialized as singletons
    by assigning different values for each token.
 */
typedef enum Type {
    TOKEN_EOF = 0,

    TOKEN_MESSAGE_SYMBOL = 1,
    TOKEN_ID_SYMBOL = 2,
    TOKEN_SYNTAX_SYMBOL = 3,

    TOKEN_INTEGER = 11,
    TOKEN_FLOAT = 12,

    TOKEN_STRING = 111,

    TOKEN_IDENTIFIER = 201,
} Type;

#endif
