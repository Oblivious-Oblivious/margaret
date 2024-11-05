#ifndef __OPCODE_H_
#define __OPCODE_H_

#include "vm.h"

#define OP_MOV   ((Instruction)0x00)
#define OP_MOVZ  ((Instruction)0x01)
#define OP_LODZ  ((Instruction)0x02)
#define OP_ADD   ((Instruction)0x03)
#define OP_SUB   ((Instruction)0x04)
#define OP_MUL   ((Instruction)0x05)
#define OP_DIV   ((Instruction)0x06)
#define OP_PRINT ((Instruction)0x07)
#define OP_RAISE ((Instruction)0x08)
#define OP_HALT  ((Instruction)0xff)

#define dispatch_table()                                  \
  static void *_computed_gotos[256] = {                   \
    &&_computed_goto_OP_MOV,   &&_computed_goto_OP_MOVZ,  \
    &&_computed_goto_OP_LODZ,  &&_computed_goto_OP_ADD,   \
    &&_computed_goto_OP_SUB,   &&_computed_goto_OP_MUL,   \
    &&_computed_goto_OP_DIV,   &&_computed_goto_OP_PRINT, \
    &&_computed_goto_OP_RAISE, &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_ERROR,    \
    &&_computed_goto_ERROR,    &&_computed_goto_OP_HALT   \
  }

#endif
