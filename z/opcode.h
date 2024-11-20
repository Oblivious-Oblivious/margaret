#ifndef __OPCODE_H_
#define __OPCODE_H_

#define OP_MOV      ((Instruction)0x00)
#define OP_LODZ     ((Instruction)0x01)
#define OP_STOZ     ((Instruction)0x02)
#define OP_PRIM     ((Instruction)0x03)
#define OP_SEND     ((Instruction)0x04)
#define OP_INSPECT  ((Instruction)0x05)
#define OP_RAISE    ((Instruction)0x06)
#define OP_EXACTREC ((Instruction)0x07)
#define OP_GOTO     ((Instruction)0x08)
#define OP_NOP      ((Instruction)0x3e)
#define OP_HALT     ((Instruction)0x3f)

#define dispatch_table()                                     \
  static void *_computed_gotos[64] = {                       \
    &&_computed_goto_OP_MOV,   &&_computed_goto_OP_LODZ,     \
    &&_computed_goto_OP_STOZ,  &&_computed_goto_OP_PRIM,     \
    &&_computed_goto_OP_SEND,  &&_computed_goto_OP_INSPECT,  \
    &&_computed_goto_OP_RAISE, &&_computed_goto_OP_EXACTREC, \
    &&_computed_goto_OP_GOTO,  &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,       \
    &&_computed_goto_OP_NOP,   &&_computed_goto_OP_HALT      \
  }

#endif
