#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "instruction.h"
#include "object.h"
#include "opcode.h"

static Instruction *emit_example_bytecode(VM *vm) {
  Instruction *bc = NULL;

  OAk(OP_NIL, "x", NIL());
  OAk(OP_FALSE, "y", FALSE());
  OAk(OP_TRUE, "y2", TRUE());
  OAk(OP_NUMBER, "y3", NUMBER(1));
  OAk(OP_NUMBER, "z", NUMBER(10));
  OAk(OP_NUMBER, "a", NUMBER(3.14));
  OAk(OP_STRING, "msg", STRING("Hello"));
  OABC(OP_ADD, "result_add", "z", "a");
  OABC(OP_SUB, "result_sub", "result_add", "y3");
  OABC(OP_MUL, "result_mul", "result_sub", "z");
  OABC(OP_DIV, "result_div", "result_mul", "a");
  OA(OP_PRINT, "x");
  OA(OP_PRINT, "y");
  OA(OP_PRINT, "y2");
  OA(OP_PRINT, "y3");
  OA(OP_PRINT, "z");
  OA(OP_PRINT, "a");
  OA(OP_PRINT, "msg");
  OA(OP_PRINT, "result_add");
  OA(OP_PRINT, "result_sub");
  OA(OP_PRINT, "result_mul");
  OA(OP_PRINT, "result_div");
  O(OP_HALT);

  return bc;
}

#endif
