#include "evaluator.h"

#include "instruction.h"
#include "nan_tagging.h"
#include "object.h"
#include "opcode.h"
#include "primitives.h"

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

  vm->current->ip = -1;

_opcode_loop:;
  switch_opcode {
    case_opcode(OP_MOV) {
      SRA(RB);
      next_opcode;
    }
    case_opcode(OP_LODZ) {
      SRA(KZ);
      next_opcode;
    }
    case_opcode(OP_STOZ) {
      SKZ(RA);
      next_opcode;
    }
    case_opcode(OP_PRIM) {
      ptrdiff_t i;
      ptrdiff_t argc  = (ptrdiff_t)AS_NUMBER(RB)->value;
      MargValue self  = K(-1 - argc);
      MargValue *args = NULL;
      char *name      = AS_STRING(RA)->value;
      MargPrimitive *msg =
        AS_PRIMITIVE(table_get(&AS_OBJECT(self)->proto->primitives, name));
      for(i = 1; i <= argc; i++) {
        vector_add(args, K(-i));
      }
      SKZ(msg->function(vm, self, args));
      next_opcode;
    }
    case_opcode(OP_SEND) { next_opcode; }
    case_opcode(OP_PRINT) {
      SKZ(primitive_PRINT(vm, RA, NULL));
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      SKZ(primitive_RAISE(vm, RA, NULL));
      next_opcode;
    }
    case_opcode(OP_HALT) { return; }
    default_opcode { exit(1); }
  }
}
