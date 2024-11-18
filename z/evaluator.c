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
      CONST(RA);
      next_opcode;
    }
    case_opcode(OP_PRIM) {
      SKZ(primitive_PRIM(vm));
      next_opcode;
    }
    case_opcode(OP_SEND) {
      primitive_SEND(vm);
      next_opcode;
    }
    case_opcode(OP_PRINT) {
      SKZ(primitive_PRINT(vm, RA, NULL));
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      SKZ(primitive_RAISE(NULL, RA, NULL));
      next_opcode;
    }
    case_opcode(OP_EXACTREC) {
      MargValue ret_value = KZ;
      vm->current         = vm->current->bound_method;
      SKZ(ret_value);
      next_opcode;
    }
    case_opcode(OP_GOTO) {
      MargValue label  = MARG_UNDEFINED;
      char *label_name = AS_STRING(RA)->value;
      if(label_name && label_name[0] == '$' && label_name[1] == ':' &&
         label_name[2] == ':') {
        label = GET_R(table_get(&vm->global_variables, label_name));
      } else if(label_name && label_name[0] == '@' && label_name[1] == ':' &&
                label_name[2] == ':') {
        label = GET_R(
          table_get(&vm->current->bound_object->instance_variables, label_name)
        );
      } else if(label_name && label_name[0] == ':' && label_name[1] == ':') {
        label = GET_R(table_get(&vm->current->local_variables, label_name));
      } else {
        label = MARG_UNDEFINED;
      }

      if(IS_LABEL(label)) {
        vm->current->ip = AS_LABEL(label)->value;
      } else {
        SKZ(raise("Error: cannot goto to a non-label."));
      }
      next_opcode;
    }
    case_opcode(OP_NOP) { next_opcode; }
    case_opcode(OP_HALT) { return; }
    default_opcode { exit(1); }
  }
}
