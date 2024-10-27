#include "emitter.h"
#include "opcode.h"
#include "scanner.h"

#define FETCH() (vm->ip++, O)

p_inline void evaluate(VM *vm) {
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
#define raise       goto *_computed_gotos[OP_RAISE]

  vm->ip = 0;

_opcode_loop:;
  switch_opcode {
    case_opcode(OP_LOCAL) {
      RA = KBk;
      next_opcode;
    }
    case_opcode(OP_ADD) {
      if(IS_MARG_NUMBER(RB) && IS_MARG_NUMBER(RC)) {
        RA = MARG_NUMBER(AS_MARG_NUMBER(RB)->value + AS_MARG_NUMBER(RC)->value);
        next_opcode;
      } else {
        RA = MARG_STRING("TypeError: cannot add non-number values.");
        raise;
      }
    }
    case_opcode(OP_SUB) {
      if(IS_MARG_NUMBER(RB) && IS_MARG_NUMBER(RC)) {
        RA = MARG_NUMBER(AS_MARG_NUMBER(RB)->value - AS_MARG_NUMBER(RC)->value);
        next_opcode;
      } else {
        RA = MARG_STRING("TypeError: cannot subtract non-number values.");
        raise;
      }
    }
    case_opcode(OP_MUL) {
      if(IS_MARG_NUMBER(RB) && IS_MARG_NUMBER(RC)) {
        RA = MARG_NUMBER(AS_MARG_NUMBER(RB)->value * AS_MARG_NUMBER(RC)->value);
        next_opcode;
      } else {
        RA = MARG_STRING("TypeError: cannot multiply non-number values.");
        raise;
      }
    }
    case_opcode(OP_DIV) {
      if(IS_MARG_NUMBER(RC) && AS_MARG_NUMBER(RC)->value == 0.0) {
        RA = MARG_STRING("Runtime Error: Division by zero");
        raise;
      } else if(IS_MARG_NUMBER(RB) && IS_MARG_NUMBER(RC)) {
        RA = MARG_NUMBER(AS_MARG_NUMBER(RB)->value / AS_MARG_NUMBER(RC)->value);
        next_opcode;
      } else {
        RA = MARG_STRING("TypeError: cannot divide non-number values.");
        raise;
      }
    }
    case_opcode(OP_PRINT) {
      if(RA == 0) {
        printf("ZERO ??\n");
      } else if(IS_MARG_NIL(RA)) {
        printf("R%u = nil\n", A);
      } else if(IS_MARG_FALSE(RA)) {
        printf("R%u = false\n", A);
      } else if(IS_MARG_TRUE(RA)) {
        printf("R%u = true\n", A);
      } else if(IS_MARG_NUMBER(RA)) {
        printf("R%u = %g\n", A, AS_MARG_NUMBER(RA)->value);
      } else if(IS_MARG_STRING(RA)) {
        printf("R%u = \"%s\"\n", A, AS_MARG_STRING(RA)->value);
      } else {
        printf("R%u = UNKNOWN\n", A);
      }
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      fprintf(stderr, "raise: `%s`\n", AS_MARG_STRING(RA)->value);
      next_opcode;
    }
    case_opcode(OP_HALT) { return; }
    default_opcode {
      fprintf(stderr, "raise: `Unknown Opcode: %u`\n", O);
      exit(1);
    }
  }
}

int main(int argc, char **argv) {
  VM _vm = {0};
  VM *vm = &_vm;
  vm_init(vm);

  if(argc == 2 && string_equals(string_new(argv[1]), "-i")) {
    while(true) {
      emit_tokens(vm, scan("> "));
      evaluate(vm);
    }
  } else {
    emit_example_bytecode(vm);
    evaluate(vm);
  }
}
