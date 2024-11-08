#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "instruction.h"
#include "nan_tagging.h"
#include "opcode.h"

p_inline void emit_example_bytecode(VM *vm) {
  OAB(OP_MOV, LOCAL("x"), CONST(MARG_NIL()));
  OAB(OP_MOV, LOCAL("y"), CONST(MARG_FALSE()));
  OAB(OP_MOV, LOCAL("y2"), CONST(MARG_TRUE()));
  OAB(OP_MOV, LOCAL("y3"), CONST(MARG_NUMBER(1)));
  OAB(OP_MOV, LOCAL("z"), CONST(MARG_NUMBER(10)));
  OAB(OP_MOV, LOCAL("a"), CONST(MARG_NUMBER(3.14)));
  OAB(OP_MOV, LOCAL("msg"), CONST(MARG_STRING("Hello")));

  OA(OP_STOZ, LOCAL("z"));
  OA(OP_STOZ, LOCAL("a"));
  OP(OP_ADD);
  OA(OP_LODZ, LOCAL("result_add"));

  OA(OP_STOZ, LOCAL("y3"));
  OP(OP_SUB);
  OA(OP_LODZ, LOCAL("result_sub"));

  OA(OP_STOZ, LOCAL("z"));
  OP(OP_MUL);
  OA(OP_LODZ, LOCAL("result_mul"));

  OA(OP_STOZ, LOCAL("a"));
  OP(OP_DIV);
  OA(OP_LODZ, LOCAL("result_div"));

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
  OA(OP_STOZ, INSTANCE("@count"));
  OA(OP_STOZ, GLOBAL("$max"));
  OP(OP_ADD);
  OA(OP_LODZ, LOCAL("total"));
  OA(OP_STOZ, CONST(MARG_NUMBER(39)));
  OP(OP_ADD);
  OA(OP_LODZ, LOCAL("total"));
  OA(OP_PRINT, LOCAL("total"));
  OA(OP_PRINT, INSTANCE("@count"));
  OA(OP_PRINT, GLOBAL("$max"));

  /* 1 + 2 + 3 + 5 + 7 + 11 + 13 */
  /* (+ (+ (+ (+ (+ (+ 1 2) 3) 5) 7) 11) 13) */
  OA(OP_STOZ, CONST(MARG_NUMBER(1)));
  OA(OP_STOZ, CONST(MARG_NUMBER(2)));
  OP(OP_ADD);

  OA(OP_STOZ, CONST(MARG_NUMBER(3)));
  OP(OP_ADD);

  OA(OP_STOZ, CONST(MARG_NUMBER(5)));
  OP(OP_ADD);

  OA(OP_STOZ, CONST(MARG_NUMBER(7)));
  OP(OP_ADD);

  OA(OP_STOZ, CONST(MARG_NUMBER(11)));
  OP(OP_ADD);

  OA(OP_STOZ, CONST(MARG_NUMBER(13)));
  OP(OP_ADD);

  OA(OP_LODZ, LOCAL("sum"));
  OA(OP_PRINT, LOCAL("sum"));

  /* exit */
  OP(OP_HALT);
}

#endif
