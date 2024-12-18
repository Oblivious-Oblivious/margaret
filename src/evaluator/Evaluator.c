#include "Evaluator.h"

#include "../opcode/instruction.h"
#include "../opcode/opcodes.h"
#include "../primitives/MargaretPrimitives.h"

#define FETCH() (vm->current->ip++, O)

#define goto_helper(label)                                 \
  if(IS_LABEL(label)) {                                    \
    vm->current     = AS_OBJECT(label)->bound_vm->current; \
    vm->current->ip = AS_LABEL(label)->value;              \
  } else {                                                 \
    SKZ(raise("Error: cannot goto to a non-label."));      \
  }

#define proc_helper(proc_value)                    \
  ptrdiff_t argc = AS_INTEGER(KB)->value;          \
  if(IS_UNDEFINED(proc_value)) {                   \
    raise("Error: cannot call a non-proc value."); \
  } else {                                         \
    ptrdiff_t i;                                   \
    MargValue *args = NULL;                        \
    for(i = 1; i <= argc; i++) {                   \
      vector_add(args, K(-i));                     \
    }                                              \
    vm->current = AS_METHOD(proc_value);           \
    for(i = 0; i < argc; i++) {                    \
      SET_L(i, args[i]);                           \
    }                                              \
    vector_free(args);                             \
  }

#define assignment_helper(self, rvalue)                                      \
  if(IS_VARIABLE(rvalue)) {                                                  \
    rvalue = AS_VARIABLE(rvalue)->value;                                     \
  }                                                                          \
  if(IS_VARIABLE(self)) {                                                    \
    if(AS_VARIABLE(self)->type == VAR_TYPE_GLOBAL) {                         \
      AS_VARIABLE(GET_G(GLOBAL(AS_VARIABLE(self)->name)))->value = rvalue;   \
    } else if(AS_VARIABLE(self)->type == VAR_TYPE_INSTANCE) {                \
      AS_VARIABLE(GET_I(INSTANCE(AS_VARIABLE(self)->name)))->value = rvalue; \
    } else if(AS_VARIABLE(self)->type == VAR_TYPE_LOCAL) {                   \
      AS_VARIABLE(GET_L(LOCAL(AS_VARIABLE(self)->name)))->value = rvalue;    \
    }                                                                        \
  }

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param vm -> result enum
 */
p_inline void evaluator_run(VM *vm) {
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
    case_opcode(OP_PROCK) {
      proc_helper(KA);
      next_opcode;
    }
    case_opcode(OP_PROCL) {
      proc_helper(LA);
      next_opcode;
    }
    case_opcode(OP_PROCI) {
      proc_helper(IA);
      next_opcode;
    }
    case_opcode(OP_PROCG) {
      proc_helper(GA);
      next_opcode;
    }
    case_opcode(OP_POP) {
      KPOP;
      next_opcode;
    }
    case_opcode(OP_PRIM) {
      char *name     = AS_STRING(KA)->value;
      ptrdiff_t argc = AS_INTEGER(KB)->value;
      MargValue args = MARG_TENSOR();
      MargValue prim_msg;
      ptrdiff_t i;

      if(argc > 0) {
        vector_initialize_n(AS_TENSOR(args)->value, argc);
        for(i = argc - 1; i >= 0; i--) {
          MargValue v = KPOP;
          if(IS_VARIABLE(v)) {
            v = AS_VARIABLE(v)->value;
          }
          AS_TENSOR(args)->value[i] = v;
        }
      }
      KPOP;

      prim_msg = table_get(&vm->primitives, name);
      if(IS_UNDEFINED(prim_msg)) {
        SKZ(raise("Error: cannot call because primitive does not exist."));
      } else {
        KPUSH(AS_PRIMITIVE(prim_msg)->function(vm, args));
      }
      next_opcode;
    }
    case_opcode(OP_SEND) {
      char *name      = AS_STRING(KA)->value;
      ptrdiff_t argc  = AS_INTEGER(KB)->value;
      MargValue self  = K(-argc - 1);
      MargValue *args = NULL;
      MargValue msg_value;

      /* NOTE - Dispatch method from delegation chain */
      MargValue curr_object = self;
      if(IS_VARIABLE(curr_object)) {
        curr_object = AS_VARIABLE(curr_object)->value;
      }
      msg_value = table_get(&AS_OBJECT(curr_object)->messages, name);
      while(IS_UNDEFINED(msg_value) && !IS_MARGARET(curr_object)) {
        curr_object = QNAN_BOX(AS_OBJECT(curr_object)->proto);
        msg_value   = table_get(&AS_OBJECT(curr_object)->messages, name);
      }

      if(IS_UNDEFINED(msg_value)) {
        raise("Error: cannot send because message does not exist.");
      } else {
        MargValue l, r;
        ptrdiff_t i;

        /* NOTE - Grab arguments from caller */
        if(argc > 0) {
          vector_initialize_n(args, argc);
          for(i = argc; i >= 0; i--) {
            args[i] = KPOP;
          }
        }

        /* NOTE - Store current method as bound for return */
        AS_METHOD(msg_value)->bound_method = vm->current;
        /* NOTE - Switch to method called */
        vm->current                        = AS_METHOD(msg_value);
        /* NOTE - Carry self from caller and mask on method */
        SET_I(INSTANCE("@self"), self);
        /* NOTE - Assign arguments to method locals */
        for(i = 0; i < argc; i++) {
          if((size_t)i < vector_size(vm->current->argument_names) &&
             vm->current->argument_names[i] != NULL) {
            l = L(vm->current->argument_names[i]);
            r = args[i + 1];
            assignment_helper(l, r);
          }
        }
      }
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      SKZ(__PRIM_RAISE(NULL, KA));
      next_opcode;
    }
    case_opcode(OP_EXACTREC) {
      MargValue ret_value = KPOP;
      vm->current->ip     = -1;
      vm->current         = vm->current->bound_method;
      /* TODO - Check if any memory can be freed */
      KPUSH(ret_value);
      next_opcode;
    }
    case_opcode(OP_ASSIGN) {
      MargValue rvalue = KPOP;
      MargValue self   = KPOP;
      assignment_helper(self, rvalue);
      KPUSH(rvalue);
      next_opcode;
    }
    /* case_opcode(OP_INCLUDE) {
      uint8_t *previous_bytecode = vm->current->bytecode;
      uint8_t *previous_position = vm->current->ip;

      MargValue filename = fs_pop(vm->sp);
      fs_pop(vm->sp);
      vm->filename = AS_STRING(filename)->value;

      EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(LOAD(vm))))));

      vm->current->bytecode = previous_bytecode;
      vm->current->ip       = previous_position;
      vm->sp++;
      next_opcode;
    } */
    case_opcode(OP_NOP) { next_opcode; }
    case_opcode(OP_HALT) { return; }
    default_opcode { exit(1); }
  }
}

MargValue evaluator_evaluate(VM *vm) {
  if(vm->error) {
    return MARG_UNDEFINED;
  }

  evaluator_run(vm);
  vm_free_formal_bytecode();

  if(vector_size(vm->current->bytecode) == 1) {
    return MARG_UNDEFINED;
  } else {
    return KZ;
  }
}
