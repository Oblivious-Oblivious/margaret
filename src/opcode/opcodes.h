#ifndef __OPCODES_H_
#define __OPCODES_H_

#define OP_STOZK     ((Instruction)0x00)
#define OP_STOZL     ((Instruction)0x01)
#define OP_STOZI     ((Instruction)0x02)
#define OP_STOZG     ((Instruction)0x03)
#define OP_LODZL     ((Instruction)0x04)
#define OP_LODZI     ((Instruction)0x05)
#define OP_LODZG     ((Instruction)0x06)
#define OP_GOTO      ((Instruction)0x07)
#define OP_POP       ((Instruction)0x08)
#define OP_TENSOR    ((Instruction)0x09)
#define OP_TUPLE     ((Instruction)0x0a)
#define OP_TABLE     ((Instruction)0x0b)
#define OP_BITSTRING ((Instruction)0x0c)
#define OP_PRIM      ((Instruction)0x0d)
#define OP_SEND      ((Instruction)0x0e)
#define OP_PCALL     ((Instruction)0x0f)
#define OP_PCALLARGS ((Instruction)0x10)
#define OP_RAISE     ((Instruction)0x11)
#define OP_EXACTREC  ((Instruction)0x12)
#define OP_ASSIGN    ((Instruction)0x13)
#define OP_NOP       ((Instruction)0x3e)
#define OP_HALT      ((Instruction)0x3f)

#define dispatch_table()                                       \
  static void *_computed_gotos[64] = {                         \
    &&_computed_goto_OP_STOZK,     &&_computed_goto_OP_STOZL,  \
    &&_computed_goto_OP_STOZI,     &&_computed_goto_OP_STOZG,  \
    &&_computed_goto_OP_LODZL,     &&_computed_goto_OP_LODZI,  \
    &&_computed_goto_OP_LODZG,     &&_computed_goto_OP_GOTO,   \
    &&_computed_goto_OP_POP,       &&_computed_goto_OP_TENSOR, \
    &&_computed_goto_OP_TUPLE,     &&_computed_goto_OP_TABLE,  \
    &&_computed_goto_OP_BITSTRING, &&_computed_goto_OP_PRIM,   \
    &&_computed_goto_OP_SEND,      &&_computed_goto_OP_PCALL,  \
    &&_computed_goto_OP_PCALLARGS, &&_computed_goto_OP_RAISE,  \
    &&_computed_goto_OP_EXACTREC,  &&_computed_goto_OP_ASSIGN, \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_ERROR,        &&_computed_goto_ERROR,     \
    &&_computed_goto_OP_NOP,       &&_computed_goto_OP_HALT    \
  }

#endif
