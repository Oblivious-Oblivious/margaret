#ifndef __OPCODES_H_
#define __OPCODES_H_

// TODO FIX OPCODE NUMBERING
#define OP_HALT                   0x00
#define OP_POP                    0xfd

#define OP_PUT_NIL                0x01
#define OP_PUT_TRUE               0x02
#define OP_PUT_FALSE              0x03

#define OP_PUT_SELF               0x42
#define OP_PUT_SUPER              0x43

#define OP_PUT_MINUS_1            0x04
#define OP_PUT_0                  0x05
#define OP_PUT_1                  0x06
#define OP_PUT_2                  0x07

#define OP_PUT_OBJECT             0x08
#define OP_PUT_OBJECT_WORD        0x33
#define OP_PUT_OBJECT_DWORD       0x09

#define OP_PUT_TENSOR             0xef
#define OP_PUT_TENSOR_WORD        0x55
#define OP_PUT_TENSOR_DWORD       0xee
// #define OP_PUT_TUPLE              0x??
// #define OP_PUT_TUPLE_WORD         0x??
// #define OP_PUT_TUPLE_DWORD        0x??
#define OP_PUT_HASH               0xed
#define OP_PUT_HASH_WORD          0x56
#define OP_PUT_HASH_DWORD         0xec
// #define OP_PUT_BITSTRING          0x??
// #define OP_PUT_BITSTRING_WORD     0x??
// #define OP_PUT_BITSTRING_DWORD    0x??

// TODO OP_JUMP_LOCAL -> Jumps into a label in the same context (fast jump)
// TODO OP_JUMP -> Jumps into a label on different context (searches object->message->method->proc->activation_record)
// TODO Label, LabelLocal primitives that store position in bytecode
// #define OP_PUT_LABEL              0x??
// #define OP_GOTO                   0x??
// #define OP_GOTO_LOCAL             0x??

#define OP_SET_GLOBAL             0x0a
#define OP_SET_GLOBAL_WORD        0x57
#define OP_SET_GLOBAL_DWORD       0x0b
#define OP_SET_INSTANCE           0x0c
#define OP_SET_INSTANCE_WORD      0x58
#define OP_SET_INSTANCE_DWORD     0x0d
#define OP_SET_LOCAL              0x0e
#define OP_SET_LOCAL_WORD         0x59
#define OP_SET_LOCAL_DWORD        0x0f

#define OP_GET_GLOBAL             0x10
#define OP_GET_GLOBAL_WORD        0x60
#define OP_GET_GLOBAL_DWORD       0x11
#define OP_GET_INSTANCE           0x12
#define OP_GET_INSTANCE_WORD      0x61
#define OP_GET_INSTANCE_DWORD     0x13
#define OP_GET_LOCAL              0x14
#define OP_GET_LOCAL_WORD         0x62
#define OP_GET_LOCAL_DWORD        0x15

#define OP_SEND                   0x1a
#define OP_SEND_WORD              0x66
#define OP_SEND_DWORD             0x1b
#define OP_CLONE_OBJECT           0x1c
#define OP_BIND_METHOD            0x19
#define OP_EXIT_ACTIVATION_RECORD 0x18

// $Margaret
#define OP_PRIM_MARGARET_PUTS     0xff

// $Proc
#define OP_PRIM_PROC_CALL         0x16
#define OP_PRIM_PROC_CALL_PARAMS  0x17

// $Integer
#define OP_PRIM_INTEGER_ADD       0x1d
#define OP_PRIM_INTEGER_SUB       0x1e
#define OP_PRIM_INTEGER_MUL       0x1f
#define OP_PRIM_INTEGER_DIV       0x20
#define OP_PRIM_INTEGER_ABS       0x21
#define OP_PRIM_INTEGER_EQUALS    0x22
#define OP_PRIM_INTEGER_LT        0x23
#define OP_PRIM_INTEGER_GT        0x24
#define OP_PRIM_INTEGER_LTE       0x25
#define OP_PRIM_INTEGER_GTE       0x26
#define OP_PRIM_INTEGER_INCR      0x27
#define OP_PRIM_INTEGER_DECR      0x28
#define OP_PRIM_INTEGER_DOUBLE    0x29

#endif
