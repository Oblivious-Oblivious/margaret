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
#define OP_PUT_TUPLE              0x11
#define OP_PUT_TUPLE_WORD         0x12
#define OP_PUT_TUPLE_DWORD        0x13
#define OP_PUT_TABLE              0x14
#define OP_PUT_TABLE_WORD         0x15
#define OP_PUT_TABLE_DWORD        0x16
#define OP_PUT_BITSTRING          0x17
#define OP_PUT_BITSTRING_WORD     0x18
#define OP_PUT_BITSTRING_DWORD    0x19
#define OP_PUT_LABEL              0x1a
#define OP_GOTO                   0x1b
#define OP_GOTO_WORD              0x1c
#define OP_GOTO_DWORD             0x1d
#define OP_SET_GLOBAL             0x1e
#define OP_SET_GLOBAL_WORD        0x1f
#define OP_SET_GLOBAL_DWORD       0x20
#define OP_SET_INSTANCE           0x21
#define OP_SET_INSTANCE_WORD      0x22
#define OP_SET_INSTANCE_DWORD     0x23
#define OP_SET_LOCAL              0x24
#define OP_SET_LOCAL_WORD         0x25
#define OP_SET_LOCAL_DWORD        0x26
#define OP_GET_GLOBAL             0x27
#define OP_GET_GLOBAL_WORD        0x28
#define OP_GET_GLOBAL_DWORD       0x29
#define OP_GET_INSTANCE           0x2a
#define OP_GET_INSTANCE_WORD      0x2b
#define OP_GET_INSTANCE_DWORD     0x2c
#define OP_GET_LOCAL              0x2d
#define OP_GET_LOCAL_WORD         0x2e
#define OP_GET_LOCAL_DWORD        0x2f
#define OP_SEND                   0x30
#define OP_SEND_WORD              0x31
#define OP_SEND_DWORD             0x32
#define OP_EXIT_ACTIVATION_RECORD 0x33
#define OP_PUTS                   0x34
#define OP_INCLUDE                0x35

/* NOTE - primitives */
#define OP_PRIM_MESSAGES       0xff
#define OP_PRIM_OBJECT_ID      0xfe
#define OP_PRIM_TO_STRING      0xfd
#define OP_PRIM_EQUALS         0xfc
#define OP_PRIM_EQUALS_NUMERIC 0xfb
#define OP_PRIM_DNU            0xfa
#define OP_PRIM_CLONE_OBJECT   0xf9
#define OP_PRIM_BIND_METHOD    0xf8
#define OP_PRIM_ADD            0xf7
#define OP_PRIM_SUB            0xf6
#define OP_PRIM_MUL            0xf5
#define OP_PRIM_DIV            0xf4
#define OP_PRIM_ABS            0xf3
#define OP_PRIM_LT             0xf2
#define OP_PRIM_GT             0xf1
#define OP_PRIM_LTE            0xf0
#define OP_PRIM_GTE            0xef
#define OP_PRIM_INCR           0xee
#define OP_PRIM_DECR           0xed
#define OP_PRIM_DOUBLE         0xec

#endif
