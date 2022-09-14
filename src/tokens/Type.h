#ifndef __TYPE_H_
#define __TYPE_H_

typedef enum Type {
    TOKEN_EOF = 0,

    TOKEN_MESSAGE_SYMBOL = 1,
    TOKEN_ID_SYMBOL = 2,
    TOKEN_SYNTAX_SYMBOL = 3,

    TOKEN_INTEGER = 11,
    TOKEN_FLOAT = 12,

    TOKEN_CHAR = 111,
    TOKEN_STRING = 112,

    TOKEN_IDENTIFIER = 201,
} Type;

#endif
