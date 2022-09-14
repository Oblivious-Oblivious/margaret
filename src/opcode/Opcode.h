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

#define PUSH_NIL                         0x00
#define PUSH_TRUE                        0x01
#define PUSH_FALSE                       0x02
#define PUSH_SELF                        0x03
#define PUSH_SUPER                       0x04
#define PUSH_0                           0x05
#define PUSH_1                           0x06
#define PUSH_MINUS_1                     0x07
#define PUSH_2                           0x08
#define PUSH_INTEGER                     0x09
#define PUSH_FLOAT                       0x0a
#define PUSH_CHAR                        0x0b
#define PUSH_STRING                      0x0c
#define PUSH_VARIABLE                    0x0d
#define PUSH_INSTANCE                    0x0e
#define PUSH_TENSOR                      0x0f
#define PUSH_HASH                        0x10

#define START_PUSH_BLOCK                 0x11
#define END_PUSH_BLOCK                   0x12

#define START_PUSH_C_FUNCTION            0x13
#define END_PUSH_C_FUNCTION              0x14

#define START_PUSH_UNARY_METHOD          0x15
#define END_PUSH_UNARY_METHOD            0x16
#define START_PUSH_BINARY_METHOD         0x17
#define END_PUSH_BINARY_METHOD           0x18
#define START_PUSH_KEYWORD_METHOD        0x19
#define END_PUSH_KEYWORD_METHOD          0x1a

#define POP                              0x1b
// #define POPN                             0x1c

#define STORE                            0x1d
// #define STORE_LOCAL                      0x1e
// #define STORE_GLOBAL                     0x1f
// #define STORE_UPVALUE                    0x20
#define STORE_INSTANCE                   0x21

// #define LABEL                            0x22

// #define JUMP                             0x23
// #define JUMP_IF_ZERO                     0x24
// #define JUMP_IF_NOT_ZERO                 0x25
// #define JUMP_IF_TRUE                     0x26
// #define JUMP_IF_FALSE                    0x27

// #define LONGJUMP                         0x28
// #define LONGJUMP_IF_ZERO                 0x29
// #define LONGJUMP_IF_NOT_ZERO             0x2a
// #define LONGJUMP_IF_TRUE                 0x2b
// #define LONGJUMP_IF_FALSE                0x2c

// #define RETURN                           0x2d
// #define RETURN_NIL                       0x2e
// #define RETURN_TRUE                      0x2f
// #define RETURN_FALSE                     0x30
// #define RETURN_STACK_TOP                 0x31

#define UNARY                            0x32
// ... most used unaries
// ...
// ...
#define BINARY                           0x33
// ... most used binaries
// ...
// ...
#define KEYWORD                          0x34
// ... most used keywords
// ...
// ...

// #define SELF_UNARY                       0x35
// #define SELF_BINARY                      0x36
// #define SELF_KEYWORD                     0x37

// #define SUPER_UNARY                      0x38
// #define SUPER_BINARY                     0x39
// #define SUPER_KEYWORD                    0x3a

#endif
