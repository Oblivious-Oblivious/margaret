#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "instruction.h"
#include "object.h"
#include "opcode.h"

p_inline void emit_example_bytecode(VM *vm) {
  OAB(OP_MOV, LOCAL("x"), CONST(MARG_NIL()));
  OAB(OP_MOV, LOCAL("y"), CONST(MARG_FALSE()));
  OAB(OP_MOV, LOCAL("y2"), CONST(MARG_TRUE()));
  OAB(OP_MOV, LOCAL("y3"), CONST(MARG_NUMBER(1)));
  OAB(OP_MOV, LOCAL("z"), CONST(MARG_NUMBER(10)));
  OAB(OP_MOV, LOCAL("a"), CONST(MARG_NUMBER(3.14)));
  OAB(OP_MOV, LOCAL("msg"), CONST(MARG_STRING("Hello")));
  OABC(OP_ADD, LOCAL("result_add"), LOCAL("z"), LOCAL("a"));
  OABC(OP_SUB, LOCAL("result_sub"), LOCAL("result_add"), LOCAL("y3"));
  OABC(OP_MUL, LOCAL("result_mul"), LOCAL("result_sub"), LOCAL("z"));
  OABC(OP_DIV, LOCAL("result_div"), LOCAL("result_mul"), LOCAL("a"));
  OA(OP_PRINT, LOCAL("x"));
  OA(OP_PRINT, LOCAL("y"));
  OA(OP_PRINT, LOCAL("y2"));
  OA(OP_PRINT, LOCAL("y3"));
  OA(OP_PRINT, LOCAL("z"));
  OA(OP_PRINT, LOCAL("a"));
  OA(OP_PRINT, LOCAL("msg"));
  OA(OP_PRINT, LOCAL("result_add"));
  OA(OP_PRINT, LOCAL("result_sub"));
  OA(OP_PRINT, LOCAL("result_mul"));
  OA(OP_PRINT, LOCAL("result_div"));

  OAB(OP_MOV, INSTANCE("@count"), CONST(MARG_NUMBER(0)));
  OAB(OP_MOV, GLOBAL("$max"), CONST(MARG_NUMBER(3)));
  OABC(OP_ADD, LOCAL("total"), INSTANCE("@count"), GLOBAL("$max"));
  OABC(OP_ADD, LOCAL("total"), LOCAL("total"), CONST(MARG_NUMBER(39)));
  OA(OP_PRINT, LOCAL("total"));

  /* exit */
  OP(OP_HALT);
}

#endif
