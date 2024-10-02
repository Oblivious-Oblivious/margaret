#include "emitter.h"

static void evaluate(VM *vm) {
#if defined(__GNUC__) || defined(__clang__)
  #include "dispatch_table.h"
  dispatch_table();
  #define switch_opcode   goto *_computed_gotos[FETCH(i)];
  #define case_opcode(op) _computed_goto_##op:
  #define default_opcode  _computed_goto_##ERROR:
#else
  #define switch_opcode   switch(FETCH(i))
  #define case_opcode(op) case(op):
  #define default_opcode  default:
#endif

#define next_opcode \
  vm->ip++;         \
  goto _opcode_loop
#define skip_opcode goto _opcode_loop

  uint32_t i;
_opcode_loop:;
  i = vm->bytecode[vm->ip];

  switch_opcode {
    case_opcode(OP_NIL) {
      vm->registers[A(i)] = NIL();
      next_opcode;
    }
    case_opcode(OP_FALSE) {
      vm->registers[A(i)] = FALSE();
      next_opcode;
    }
    case_opcode(OP_TRUE) {
      vm->registers[A(i)] = TRUE();
      next_opcode;
    }
    case_opcode(OP_NUMBER) {
      vm->registers[A(i)] = vm->constants[Bk(i)];
      next_opcode;
    }
    case_opcode(OP_STRING) {
      vm->registers[A(i)] = vm->constants[Bk(i)];
      next_opcode;
    }
    case_opcode(OP_ADD) {
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value +
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_SUB) {
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value -
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_MUL) {
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value *
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_DIV) {
      if(AS_NUMBER(vm->registers[C(i)])->value == 0.0) {
        fprintf(stderr, "Runtime Error: Division by zero\n");
        exit(1);
      }
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value /
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_JUMP) {
      if(Bk(i) >= MAX_CONSTANTS) {
        fprintf(stderr, "Invalid jump target: %u\n", Bk(i));
        exit(1);
      }
      vm->ip = Bk(i);
      skip_opcode;
    }
    case_opcode(OP_JUMP_IF_FALSE) {
      Value condition = vm->registers[A(i)];
      bool is_false   = IS_FALSE(condition) || IS_NIL(condition);
      if(is_false) {
        if(Bk(i) >= MAX_CONSTANTS) {
          fprintf(stderr, "Invalid jump target: %u\n", Bk(i));
          exit(1);
        }
        vm->ip = Bk(i);
        skip_opcode;
      } else {
        next_opcode;
      }
    }
    case_opcode(OP_PRINT) {
      Value v = vm->registers[A(i)];
      if(IS_NIL(v)) {
        printf("R%d = nil\n", A(i));
      } else if(IS_FALSE(v)) {
        printf("R%d = false\n", A(i));
      } else if(IS_TRUE(v)) {
        printf("R%d = true\n", A(i));
      } else if(IS_NUMBER(v)) {
        printf("R%d = %g\n", A(i), AS_NUMBER(v)->value);
      } else if(IS_STRING(v)) {
        printf("R%d = \"%s\"\n", A(i), AS_STRING(v)->value);
      } else {
        printf("R%d = UNKNOWN\n", A(i));
      }
      next_opcode;
    }
    case_opcode(OP_HALT) {
      printf("HALT: Stopping VM execution.\n");
      exit(0);
    }
    default_opcode {
      fprintf(stderr, "Unknown opcode: %d\n", FETCH(i));
      exit(1);
    }
  }
}

int main(void) {
  VM _vm = {0};
  VM *vm = &_vm;

  vm_init(vm);
  vm->bytecode = emit_example_bytecode(vm);
  evaluate(vm);
}
