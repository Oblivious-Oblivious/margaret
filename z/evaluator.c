#include "evaluator.h"

#include "instruction.h"
#include "nan_tagging.h"
#include "opcode.h"

static void primitive_RAISE(Value message) {
  fprintf(stderr, "raise: `%s`\n", AS_MARG_STRING(message)->value);
}

#define FETCH() (vm->current->ip++, O)

void evaluate(VM *vm) {
#if defined(__GNUC__) || defined(__clang__)
  dispatch_table();
  #define switch_opcode   goto *_computed_gotos[FETCH()];
  #define case_opcode(op) _computed_goto_##op:
  #define default_opcode  _computed_goto_##ERROR:
#else
  #define switch_opcode   switch(FETCH())
  #define case_opcode(op) case(op):
  #define default_opcode  default:
#endif

#define next_opcode goto _opcode_loop
#define raise(msg)  primitive_RAISE(MARG_STRING(msg))

  vm->current->ip = -1;

_opcode_loop:;
  switch_opcode {
    case_opcode(OP_MOV) {
      SRA(RB);
      next_opcode;
    }
    case_opcode(OP_MOVZ) {
      SRA(RZ);
      next_opcode;
    }
    case_opcode(OP_LODZ) {
      SRZ(RA);
      next_opcode;
    }
    case_opcode(OP_ADD) {
      if(IS_MARG_NUMBER(K(-2)) && IS_MARG_NUMBER(K(-1))) {
        SRZ(MARG_NUMBER(
          AS_MARG_NUMBER(K(-2))->value + AS_MARG_NUMBER(K(-1))->value
        ));
        next_opcode;
      } else {
        raise("TypeError: cannot add non-number values.");
      }
    }
    case_opcode(OP_SUB) {
      if(IS_MARG_NUMBER(K(-2)) && IS_MARG_NUMBER(K(-1))) {
        SRZ(MARG_NUMBER(
          AS_MARG_NUMBER(K(-2))->value - AS_MARG_NUMBER(K(-1))->value
        ));
        next_opcode;
      } else {
        raise("TypeError: cannot subtract non-number values.");
      }
    }
    case_opcode(OP_MUL) {
      if(IS_MARG_NUMBER(K(-2)) && IS_MARG_NUMBER(K(-1))) {
        SRZ(MARG_NUMBER(
          AS_MARG_NUMBER(K(-2))->value * AS_MARG_NUMBER(K(-1))->value
        ));
        next_opcode;
      } else {
        raise("TypeError: cannot multiply non-number values.");
      }
    }
    case_opcode(OP_DIV) {
      if(IS_MARG_NUMBER(K(-1)) && AS_MARG_NUMBER(K(-1))->value == 0.0) {
        raise("Runtime Error: Division by zero");
      } else if(IS_MARG_NUMBER(K(-2)) && IS_MARG_NUMBER(K(-1))) {
        SRZ(MARG_NUMBER(
          AS_MARG_NUMBER(K(-2))->value / AS_MARG_NUMBER(K(-1))->value
        ));
        next_opcode;
      } else {
        raise("TypeError: cannot divide non-number values.");
      }
    }
    case_opcode(OP_PRINT) {
      if(RA == 0) {
        printf("ZERO ??\n");
      } else if(IS_MARG_NIL(RA)) {
        printf("R%zu = nil\n", GET_INDEX(A));
      } else if(IS_MARG_FALSE(RA)) {
        printf("R%zu = false\n", GET_INDEX(A));
      } else if(IS_MARG_TRUE(RA)) {
        printf("R%zu = true\n", GET_INDEX(A));
      } else if(IS_MARG_NUMBER(RA)) {
        printf("R%zu = %g\n", GET_INDEX(A), AS_MARG_NUMBER(RA)->value);
      } else if(IS_MARG_STRING(RA)) {
        printf("R%zu = \"%s\"\n", GET_INDEX(A), AS_MARG_STRING(RA)->value);
      } else {
        printf("R%zu = UNKNOWN\n", GET_INDEX(A));
      }
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      primitive_RAISE(RA);
      next_opcode;
    }
    case_opcode(OP_HALT) { return; }
    default_opcode { exit(1); }
  }
}
