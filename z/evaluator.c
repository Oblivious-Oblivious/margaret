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
      ptrdiff_t i;
      ptrdiff_t argc  = AS_NUMBER(RB)->value;
      MargValue self  = K(-1 - argc);
      MargValue *args = NULL;
      char *name      = AS_STRING(RA)->value;

      MargValue prim_msg = table_get(&AS_OBJECT(self)->proto->primitives, name);
      if(IS_UNDEFINED(prim_msg)) {
        SKZ(raise("Error: cannot call because primitive does not exist."));
      } else {
        for(i = 1; i <= argc; i++) {
          /* TODO - Turn this into a MARG_TENSOR to be included in the GC */
          vector_add(args, K(-i));
        }
        SKZ(AS_PRIMITIVE(prim_msg)->function(vm, self, args));
      }
      next_opcode;
    }
    case_opcode(OP_SEND) {
      ptrdiff_t i;
      MargValue msg_value;
      EmeraldsTable object_messages;
      ptrdiff_t argc  = AS_NUMBER(RB)->value;
      MargValue self  = K(-1 - argc);
      MargValue *args = NULL;
      char *name      = AS_STRING(RA)->value;

      object_messages = AS_OBJECT(self)->messages;
      msg_value       = table_get(&object_messages, name);
      if(IS_UNDEFINED(msg_value)) {
        raise("Error: cannot send because message does not exist.");
      } else {
        for(i = 1; i <= argc; i++) {
          /* TODO - Probably also should be a MARG_TENSOR */
          vector_add(args, K(-i));
        }
        vm->current = AS_METHOD(msg_value);
        for(i = 0; i < argc; i++) {
          vm->current->local_registers[LOCAL(vm->current->arguments[i])] =
            args[i];
        }
        vector_free(args);
      }
      next_opcode;
    }
    case_opcode(OP_INSPECT) {
      SKZ(primitive_INSPECT(vm, RA, NULL));
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
