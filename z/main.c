#include "emitter.h"
#include "scanner.h"

#define FETCH() (vm->ip++, OP)
#define READ()  (vm->bytecode[vm->ip - 1])

#define R(i) (vm->registers[i])
#define K(i) (vm->constants[i])

#define OP (((READ()) & 0xffff000000000000) >> 48)
#define A  (((READ()) & 0x0000ffff00000000) >> 32)
#define B  (((READ()) & 0x00000000ffff0000) >> 16)
#define C  (((READ()) & 0x000000000000ffff) >> 0)
/* TODO - Implement Ak */
#define Bk ((B << 16) | C)

#define RA  R(A)
#define RB  R(B)
#define RC  R(C)
/* TODO - Implement KAk */
#define KBk K(Bk)

static void evaluate(VM *vm) {
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
#define skip_opcode goto _opcode_loop

  vm->ip = 0;

_opcode_loop:;
  switch_opcode {
    case_opcode(OP_FALSE) {
      RA = FALSE();
      next_opcode;
    }
    case_opcode(OP_NIL) {
      RA = NIL();
      next_opcode;
    }
    case_opcode(OP_TRUE) {
      RA = TRUE();
      next_opcode;
    }
    case_opcode(OP_NUMBER) {
      RA = KBk;
      next_opcode;
    }
    case_opcode(OP_STRING) {
      RA = KBk;
      next_opcode;
    }
    case_opcode(OP_ADD) {
      RA = NUMBER(AS_NUMBER(RB)->value + AS_NUMBER(RC)->value);
      next_opcode;
    }
    case_opcode(OP_SUB) {
      RA = NUMBER(AS_NUMBER(RB)->value - AS_NUMBER(RC)->value);
      next_opcode;
    }
    case_opcode(OP_MUL) {
      RA = NUMBER(AS_NUMBER(RB)->value * AS_NUMBER(RC)->value);
      next_opcode;
    }
    case_opcode(OP_DIV) {
      if(AS_NUMBER(RC)->value == 0.0) {
        fprintf(stderr, "Runtime Error: Division by zero\n");
        exit(1);
      }
      RA = NUMBER(AS_NUMBER(RB)->value / AS_NUMBER(RC)->value);
      next_opcode;
    }
    case_opcode(OP_JUMP) {
      vm->ip = Bk;
      skip_opcode;
    }
    case_opcode(OP_JUMP_IF_FALSE) {
      if(IS_FALSE(RA) || IS_NIL(RA)) {
        vm->ip = Bk;
        skip_opcode;
      } else {
        next_opcode;
      }
    }
    case_opcode(OP_PRINT) {
      if(RA == 0) {
        printf("ZERO ??\n");
      } else if(IS_NIL(RA)) {
        printf("R%zu = nil\n", A);
      } else if(IS_FALSE(RA)) {
        printf("R%zu = false\n", A);
      } else if(IS_TRUE(RA)) {
        printf("R%zu = true\n", A);
      } else if(IS_NUMBER(RA)) {
        printf("R%zu = %g\n", A, AS_NUMBER(RA)->value);
      } else if(IS_STRING(RA)) {
        printf("R%zu = \"%s\"\n", A, AS_STRING(RA)->value);
      } else {
        printf("R%zu = UNKNOWN\n", A);
      }
      next_opcode;
    }
    case_opcode(OP_HALT) { return; }
    default_opcode {
      fprintf(stderr, "Unknown opcode: %zu\n", OP);
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
      vm->bytecode = emit_tokens(vm, scan("> "));
      evaluate(vm);
    }
  } else {
    vm->bytecode = emit_example_bytecode(vm);
    evaluate(vm);
  }
}
