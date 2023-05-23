#ifndef __OPCODES_H_
#define __OPCODES_H_

#define OP_HALT                   0x00
#define OP_POP                    0x01

#define OP_PUT_NIL                0x02
#define OP_PUT_TRUE               0x03
#define OP_PUT_FALSE              0x04

#define OP_PUT_SELF               0x05
#define OP_PUT_SUPER              0x06

#define OP_PUT_MINUS_1            0x07
#define OP_PUT_0                  0x08
#define OP_PUT_1                  0x09
#define OP_PUT_2                  0x0a

#define OP_PUT_OBJECT             0x0b
#define OP_PUT_OBJECT_WORD        0x0c
#define OP_PUT_OBJECT_DWORD       0x0d

#define OP_PUT_TENSOR             0x0e
#define OP_PUT_TENSOR_WORD        0x0f
#define OP_PUT_TENSOR_DWORD       0x10
// #define OP_PUT_TUPLE              0x11
// #define OP_PUT_TUPLE_WORD         0x12
// #define OP_PUT_TUPLE_DWORD        0x13
#define OP_PUT_HASH               0x14
#define OP_PUT_HASH_WORD          0x15
#define OP_PUT_HASH_DWORD         0x16
// #define OP_PUT_BITSTRING          0x17
// #define OP_PUT_BITSTRING_WORD     0x18
// #define OP_PUT_BITSTRING_DWORD    0x19

// TODO OP_JUMP_LOCAL -> Jumps into a label in the same context (fast jump)
// TODO OP_JUMP -> Jumps into a label on different context (searches object->message->method->proc->activation_record)
// TODO Label, LabelLocal primitives that store position in bytecode
// #define OP_PUT_LABEL              0x1a
// #define OP_GOTO                   0x1b
// #define OP_GOTO_LOCAL             0x1c

#define OP_SET_GLOBAL             0x1d
#define OP_SET_GLOBAL_WORD        0x1e
#define OP_SET_GLOBAL_DWORD       0x1f
#define OP_SET_INSTANCE           0x20
#define OP_SET_INSTANCE_WORD      0x21
#define OP_SET_INSTANCE_DWORD     0x22
#define OP_SET_LOCAL              0x23
#define OP_SET_LOCAL_WORD         0x24
#define OP_SET_LOCAL_DWORD        0x25

#define OP_GET_GLOBAL             0x26
#define OP_GET_GLOBAL_WORD        0x27
#define OP_GET_GLOBAL_DWORD       0x28
#define OP_GET_INSTANCE           0x29
#define OP_GET_INSTANCE_WORD      0x2a
#define OP_GET_INSTANCE_DWORD     0x2b
#define OP_GET_LOCAL              0x2c
#define OP_GET_LOCAL_WORD         0x2d
#define OP_GET_LOCAL_DWORD        0x2e

#define OP_SEND                   0x2f
#define OP_SEND_WORD              0x30
#define OP_SEND_DWORD             0x31
#define OP_CLONE_OBJECT           0x32
#define OP_BIND_METHOD            0x33
#define OP_EXIT_ACTIVATION_RECORD 0x34

// $Margaret
#define OP_PRIM_PUTS              0xff
#define OP_PRIM_1_MESSAGES        0xfe
#define OP_PRIM_2_OBJECT_ID       0xfd
#define OP_PRIM_3_TO_STRING       0xfc
#define OP_PRIM_4_EQUALS          0xfb
#define OP_PRIM_5_EQUALS_NUMERIC  0xfa
#define OP_PRIM_6_DNU             0xf9

// $Proc
#define OP_PRIM_PROC_CALL         0x36
#define OP_PRIM_PROC_CALL_PARAMS  0x37

// $NumericProto
#define OP_PRIM_NUMERIC_ADD       0x38
#define OP_PRIM_NUMERIC_SUB       0x39
#define OP_PRIM_NUMERIC_MUL       0x3a
#define OP_PRIM_NUMERIC_DIV       0x3b
#define OP_PRIM_NUMERIC_ABS       0x3c
#define OP_PRIM_NUMERIC_EQUALS    0x3d
#define OP_PRIM_NUMERIC_LT        0x3e
#define OP_PRIM_NUMERIC_GT        0x3f
#define OP_PRIM_NUMERIC_LTE       0x40
#define OP_PRIM_NUMERIC_GTE       0x41

// $Integer
#define OP_PRIM_INTEGER_INCR      0x42
#define OP_PRIM_INTEGER_DECR      0x43
#define OP_PRIM_INTEGER_DOUBLE    0x44

#endif
