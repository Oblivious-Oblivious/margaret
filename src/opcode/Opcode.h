#ifndef __OPCODE_H_
#define __OPCODE_H_

#define OP_DECLARE_VARIABLE              0x01
#define OP_GENERATE_IDENTIFIER_POSITION  0x02
#define OP_ADD_VARIABLE_TO_VECTOR        0x03
#define OP_MAKE_VARIABLE                 0x04
#define OP_COMPILER_NEW                  0x05
#define OP_SCOPE_BEGIN                   0x06
#define OP_SCOPE_END                     0x07

//-------------------------------------------

#define OP_PUSH_NIL                      0x00
#define OP_PUSH_TRUE                     0x01
#define OP_PUSH_FALSE                    0x02
#define OP_PUSH_SELF                     0x03
#define OP_PUSH_SUPER                    0x04
#define OP_PUSH_0                        0x05
#define OP_PUSH_1                        0x06
#define OP_PUSH_MINUS_1                  0x07
#define OP_PUSH_2                        0x08
#define OP_PUSH_INTEGER                  0x09
#define OP_PUSH_FLOAT                    0x0a
#define OP_PUSH_CHAR                     0x0b
#define OP_PUSH_STRING                   0x0c
#define OP_PUSH_VARIABLE                 0x0d
#define OP_PUSH_INSTANCE                 0x0e
#define OP_PUSH_TENSOR                   0x0f
#define OP_PUSH_HASH                     0x10

#define OP_START_PUSH_BLOCK              0x11
#define OP_END_PUSH_BLOCK                0x12

#define OP_START_PUSH_C_FUNCTION         0x13
#define OP_END_PUSH_C_FUNCTION           0x14

#define OP_START_PUSH_UNARY_METHOD       0x15
#define OP_END_PUSH_UNARY_METHOD         0x16
#define OP_START_PUSH_BINARY_METHOD      0x17
#define OP_END_PUSH_BINARY_METHOD        0x18
#define OP_START_PUSH_KEYWORD_METHOD     0x19
#define OP_END_PUSH_KEYWORD_METHOD       0x1a

#define OP_POP                           0x1b
// #define OP_POPN                          0x1c

#define OP_STORE                         0x1d
// #define OP_STORE_LOCAL                   0x1e
// #define OP_STORE_GLOBAL                  0x1f
// #define OP_STORE_UPVALUE                 0x20
#define OP_STORE_INSTANCE                0x21

// #define OP_LABEL                         0x22

// #define OP_JUMP                          0x23
// #define OP_JUMP_IF_ZERO                  0x24
// #define OP_JUMP_IF_NOT_ZERO              0x25
// #define OP_JUMP_IF_TRUE                  0x26
// #define OP_JUMP_IF_FALSE                 0x27

// #define OP_LONGJUMP                      0x28
// #define OP_LONGJUMP_IF_ZERO              0x29
// #define OP_LONGJUMP_IF_NOT_ZERO          0x2a
// #define OP_LONGJUMP_IF_TRUE              0x2b
// #define OP_LONGJUMP_IF_FALSE             0x2c

// #define OP_RETURN                        0x2d
// #define OP_RETURN_NIL                    0x2e
// #define OP_RETURN_TRUE                   0x2f
// #define OP_RETURN_FALSE                  0x30
// #define OP_RETURN_STACK_TOP              0x31

#define OP_UNARY                         0x32
// ... most used unaries
// ...
// ...
#define OP_BINARY                        0x33
// ... most used binaries
// ...
// ...
#define OP_KEYWORD                       0x34
// ... most used keywords
// ...
// ...

// #define OP_SELF_UNARY                    0x35
// #define OP_SELF_BINARY                   0x36
// #define OP_SELF_KEYWORD                  0x37

// #define OP_SUPER_UNARY                   0x38
// #define OP_SUPER_BINARY                  0x39
// #define OP_SUPER_KEYWORD                 0x3a

#endif
