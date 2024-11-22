#include "evaluator.h"

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "opcode.h"
#include "primitives.h"

#define FETCH() (vm->current->ip++, O)

#define goto_helper(label)                                 \
  if(IS_LABEL(label)) {                                    \
    vm->current     = AS_OBJECT(label)->bound_vm->current; \
    vm->current->ip = AS_LABEL(label)->value;              \
  } else {                                                 \
    SKZ(raise("Error: cannot goto to a non-label."));      \
  }

static MargValue dispatch_method_from_delegation_chain(VM *vm, MargValue self) {
  char *name            = AS_STRING(KA)->value;
  MargValue curr_object = self;
  MargValue msg_value   = table_get(&AS_OBJECT(curr_object)->messages, name);
  while(IS_UNDEFINED(msg_value) && !IS_MARGARET(self)) {
    curr_object = QNAN_BOX(AS_OBJECT(curr_object)->proto);
    msg_value   = table_get(&AS_OBJECT(curr_object)->messages, name);
  }
  return msg_value;
}

static MargValue
dispatch_primitive_from_delegation_chain(VM *vm, MargValue self) {
  char *name            = AS_STRING(KA)->value;
  MargValue curr_object = self;
  MargValue prim_msg    = table_get(&AS_OBJECT(curr_object)->primitives, name);
  while(IS_UNDEFINED(prim_msg) && !IS_MARGARET(self)) {
    curr_object = QNAN_BOX(AS_OBJECT(curr_object)->proto);
    prim_msg    = table_get(&AS_OBJECT(curr_object)->primitives, name);
  }
  return prim_msg;
}

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
    case_opcode(OP_STOZK) {
      CONST(KA);
      next_opcode;
    }
    case_opcode(OP_STOZL) {
      CONST(LA);
      next_opcode;
    }
    case_opcode(OP_STOZI) {
      CONST(IA);
      next_opcode;
    }
    case_opcode(OP_STOZG) {
      CONST(GA);
      next_opcode;
    }
    case_opcode(OP_LODZL) {
      SLA(KZ);
      next_opcode;
    }
    case_opcode(OP_LODZI) {
      SIA(KZ);
      next_opcode;
    }
    case_opcode(OP_LODZG) {
      SGA(KZ);
      next_opcode;
    }
    case_opcode(OP_GOTOL) {
      MargValue label =
        GET_L(table_get(&vm->current->local_variables, AS_STRING(KA)->value));
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_GOTOI) {
      MargValue label = GET_I(table_get(
        &vm->current->bound_object->instance_variables, AS_STRING(KA)->value
      ));
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_GOTOG) {
      MargValue label =
        GET_G(table_get(&vm->global_variables, AS_STRING(KA)->value));
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_PRIM) {
      ptrdiff_t argc = AS_NUMBER(KB)->value;
      MargValue self = K(-1 - argc);

      MargValue prim_msg = dispatch_primitive_from_delegation_chain(vm, self);
      if(IS_UNDEFINED(prim_msg)) {
        SKZ(raise("Error: cannot call because primitive does not exist."));
      } else {
        ptrdiff_t i;
        MargValue *args = NULL;
        for(i = 1; i <= argc; i++) {
          /* TODO - Turn this into a MARG_TENSOR to be included in the GC */
          vector_add(args, K(-i));
        }
        SKZ(AS_PRIMITIVE(prim_msg)->function(vm, self, args));
      }
      next_opcode;
    }
    case_opcode(OP_SEND) {
      ptrdiff_t argc = AS_NUMBER(KB)->value;
      MargValue self = K(-1 - argc);

      MargValue msg_value = dispatch_method_from_delegation_chain(vm, self);
      if(IS_UNDEFINED(msg_value)) {
        raise("Error: cannot send because message does not exist.");
      } else {
        ptrdiff_t i;
        MargValue *args = NULL;
        for(i = 1; i <= argc; i++) {
          /* TODO - Probably also should be a MARG_TENSOR */
          vector_add(args, K(-i));
        }
        vm->current = AS_METHOD(msg_value);
        for(i = 0; i < argc; i++) {
          SET_L(i, args[i]);
        }
        vector_free(args);
      }
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      SKZ(primitive_RAISE(NULL, KA, NULL));
      next_opcode;
    }
    case_opcode(OP_EXACTREC) {
      MargValue ret_value = KZ;
      vm->current         = vm->current->bound_method;
      SKZ(ret_value);
      next_opcode;
    }
    case_opcode(OP_NOP) { next_opcode; }
    case_opcode(OP_HALT) { return; }
    default_opcode { exit(1); }
  }
}
