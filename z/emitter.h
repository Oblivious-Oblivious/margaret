#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "instruction.h"
#include "nan_tagging.h"
#include "opcode.h"

#define COMP_LABEL_LOCAL(name) \
  (SET_L(LOCAL(name), MARG_LABEL(name)), OP(OP_NOP))
#define COMP_LABEL_INSTANCE(name) \
  (SET_I(INSTANCE(name), MARG_LABEL(name)), OP(OP_NOP))
#define COMP_LABEL_GLOBAL(name) \
  (SET_G(GLOBAL(name), MARG_LABEL(name)), OP(OP_NOP))

p_inline void define_add_method_in_marg(VM *vm) {
  /* $Margaret-- #add : other => 420 prim_ADD : other */
  MargObject *marg = AS_OBJECT(G("$Margaret"));
  MargValue m_add  = MARG_METHOD(marg, vm->current, "add:");
  vm->current      = AS_METHOD(m_add);
  vector_add(vm->current->arguments, "other");
  OA(OP_STOZK, CONST(MARG_NUMBER(420)));
  OA(OP_STOZL, LOCAL("other"));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));
  OP(OP_EXACTREC);
  vm->current = AS_METHOD(m_add)->bound_method;
  table_add(&marg->messages, "add:", m_add);
}

p_inline void emit_example_bytecode(VM *vm) {
  OA(OP_STOZK, CONST(MARG_NIL()));
  OA(OP_LODZL, LOCAL("x"));
  OA(OP_STOZK, CONST(MARG_FALSE()));
  OA(OP_LODZL, LOCAL("y"));
  OA(OP_STOZK, CONST(MARG_TRUE()));
  OA(OP_LODZL, LOCAL("y2"));
  OA(OP_STOZK, CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("y3"));
  OA(OP_STOZK, CONST(MARG_NUMBER(10)));
  OA(OP_LODZL, LOCAL("z"));
  OA(OP_STOZK, CONST(MARG_NUMBER(3.14)));
  OA(OP_LODZL, LOCAL("a"));
  OA(OP_STOZK, CONST(MARG_STRING("Hello")));
  OA(OP_LODZL, LOCAL("msg"));

  OA(OP_STOZK, CONST(MARG_NUMBER(1)));
  OA(OP_STOZK, CONST(MARG_NUMBER(0)));
  OAB(OP_PRIM, CONST(MARG_STRING("/")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("divres"));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("divres"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));

  OA(OP_STOZL, LOCAL("z"));
  OA(OP_STOZL, LOCAL("a"));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("result_add"));

  OA(OP_STOZL, LOCAL("y3"));
  OAB(OP_PRIM, CONST(MARG_STRING("-")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("result_sub"));

  OA(OP_STOZL, LOCAL("z"));
  OAB(OP_PRIM, CONST(MARG_STRING("*")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("result_mul"));

  OA(OP_STOZL, LOCAL("a"));
  OAB(OP_PRIM, CONST(MARG_STRING("/")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("result_div"));

  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("x"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("y"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("y2"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("y3"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("z"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("a"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("msg"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZK, CONST(MARG_LABEL("::random")));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZK, CONST(MARG_PRIMITIVE("PRIM_add", NULL)));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("result_add"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("result_sub"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("result_mul"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("result_div"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));

  OA(OP_STOZK, CONST(MARG_NUMBER(0)));
  OA(OP_LODZI, INSTANCE("@count"));
  OA(OP_STOZK, CONST(MARG_NUMBER(3)));
  OA(OP_LODZG, GLOBAL("$max"));
  OA(OP_STOZI, INSTANCE("@count"));
  OA(OP_STOZG, GLOBAL("$max"));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("total"));
  OA(OP_STOZK, CONST(MARG_NUMBER(39)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));
  OA(OP_LODZL, LOCAL("total"));

  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("total"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZI, INSTANCE("@count"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZG, GLOBAL("$max"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));

  /* 1 + 2 + 3 + 5 + 7 + 11 + 13 */
  /* (+ (+ (+ (+ (+ (+ 1 2) 3) 5) 7) 11) 13) */
  OA(OP_STOZK, CONST(MARG_NUMBER(1)));
  OA(OP_STOZK, CONST(MARG_NUMBER(2)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));

  OA(OP_STOZK, CONST(MARG_NUMBER(3)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));

  OA(OP_GOTOL, CONST(MARG_STRING("::label")));

  OA(OP_STOZK, CONST(MARG_NUMBER(5)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));

  COMP_LABEL_INSTANCE("@::label");

  OA(OP_STOZK, CONST(MARG_NUMBER(7)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));

  OA(OP_GOTOG, CONST(MARG_STRING("$::label")));

  COMP_LABEL_LOCAL("::label");
  OA(OP_GOTOI, CONST(MARG_STRING("@::label")));

  COMP_LABEL_GLOBAL("$::label");

  OA(OP_STOZK, CONST(MARG_NUMBER(11)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));

  OA(OP_STOZK, CONST(MARG_NUMBER(13)));
  OAB(OP_PRIM, CONST(MARG_STRING("+")), CONST(MARG_NUMBER(1)));

  OA(OP_LODZL, LOCAL("sum"));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("sum"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));

  define_add_method_in_marg(vm);

  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZK, CONST(MARG_NUMBER(3)));
  OAB(OP_SEND, CONST(MARG_STRING("add:")), CONST(MARG_NUMBER(1)));

  OA(OP_LODZL, LOCAL("result"));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("result"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));

  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZL, LOCAL("::label"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZI, INSTANCE("@::label"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));
  OA(OP_STOZG, GLOBAL("$Margaret"));
  OA(OP_STOZG, GLOBAL("$::label"));
  OAB(OP_PRIM, CONST(MARG_STRING("inspect:")), CONST(MARG_NUMBER(1)));

  /* exit */
  OP(OP_HALT);
}

#endif
