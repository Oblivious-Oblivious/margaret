#include "Evaluator.h"

#include "../opcode/instruction.h"
#include "../opcode/opcodes.h"
#include "../primitives/MargaretPrimitives.h"
#include "../vm/compilation_pipeline.h"

#define FETCH() (vm->current->ip++, O)

#define goto_helper(label)                                 \
  if(IS_LABEL(label)) {                                    \
    vm->current     = AS_OBJECT(label)->bound_vm->current; \
    vm->current->ip = AS_LABEL(label)->value;              \
  } else {                                                 \
    KPUSH(raise("Error: cannot goto to a non-label."));    \
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
    case_opcode(OP_GOTO) {
      MargValue label  = MARG_NIL;
      char *label_name = AS_STRING(KPOP)->value;
      KPOP;

      if(label_name[0] == '\0') {
      } else if(label_name[0] == '$') {
        label = GET_G(table_get(&vm->global_variables, label_name));
      } else if(label_name[0] == '@') {
        label = GET_I(
          table_get(&vm->current->bound_object->instance_variables, label_name)
        );
      } else if(label_name[0] == ':') {
        label = GET_L(table_get(&vm->current->local_variables, label_name));
      }
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_POP) {
      KPOP;
      next_opcode;
    }
    case_opcode(OP_TENSOR) {
      ptrdiff_t i;
      ptrdiff_t number_of_elements = AS_INTEGER(KA)->value;
      MargValue tensor             = MARG_TENSOR();

      vector_initialize_n(AS_TENSOR(tensor)->value, number_of_elements);
      for(i = number_of_elements - 1; i >= 0; i--) {
        AS_TENSOR(tensor)->value[i] = KPOP;
      }

      KPUSH(tensor);
      next_opcode;
    }
    case_opcode(OP_TUPLE) {
      ptrdiff_t i;
      ptrdiff_t number_of_elements = AS_INTEGER(KA)->value;
      MargValue tuple              = MARG_TUPLE();

      vector_initialize_n(AS_TUPLE(tuple)->value, number_of_elements);
      for(i = number_of_elements - 1; i >= 0; i--) {
        AS_TUPLE(tuple)->value[i] = KPOP;
      }

      KPUSH(tuple);
      next_opcode;
    }
    case_opcode(OP_TABLE) {
      ptrdiff_t i;
      ptrdiff_t number_of_elements = AS_INTEGER(KA)->value;
      MargValue table              = MARG_TABLE();

      for(i = 0; i < number_of_elements; i += 2) {
        MargValue value = KPOP;
        MargValue key   = KPOP;
        table_add(&AS_TABLE(table)->value, AS_STRING(key)->value, value);
      }

      KPUSH(table);
      next_opcode;
    }
    case_opcode(OP_BITSTRING) {
      ptrdiff_t i;
      ptrdiff_t number_of_elements = AS_INTEGER(KA)->value;
      MargValue bitstring          = MARG_BITSTRING();

      MargValue *pairs = AS_TENSOR(MARG_TENSOR())->value;
      for(i = 0; i < number_of_elements; i += 2) {
        vector_add(pairs, KPOP);
        vector_add(pairs, KPOP);
      }

      for(i = vector_size_signed(pairs) - 1; i >= 0; i -= 2) {
        vector_add(AS_BITSTRING(bitstring)->bits->value, pairs[i]);
        vector_add(AS_BITSTRING(bitstring)->sizes->value, pairs[i - 1]);
      }

      KPUSH(bitstring);
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
        KPUSH(raise("Error: cannot call because primitive does not exist."));
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
        KPUSH(raise("Error: cannot send because message does not exist."));
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
    case_opcode(OP_PCALL) {
      MargValue proc = KPOP;
      /* NOTE - Pops margaret object since it derives from a keyword message */
      KPOP;
      if(!IS_METHOD(proc)) {
        raise("Error: cannot call a non-proc value.");
      } else {
        AS_METHOD(proc)->bound_method = vm->current;
        vm->current                   = AS_METHOD(proc);
      }
      next_opcode;
    }
    case_opcode(OP_PCALLARGS) {
      MargValue args_value = KPOP;
      MargValue proc       = KPOP;
      MargValue *args      = AS_TENSOR(args_value)->value;
      KPOP;

      if(IS_METHOD(proc)) {
        MargValue l, r;
        size_t i;
        size_t argc                   = vector_size(args);
        AS_METHOD(proc)->bound_method = vm->current;
        vm->current                   = AS_METHOD(proc);
        for(i = 0; i < argc; i++) {
          if((size_t)i < vector_size(vm->current->argument_names) &&
             vm->current->argument_names[i] != NULL) {
            l = L(vm->current->argument_names[i]);
            r = args[i];
            assignment_helper(l, r);
          }
        }
      }
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      KPUSH(__PRIM_RAISE(NULL, KA));
      next_opcode;
    }
    case_opcode(OP_EXACTREC) {
      MargValue ret_value = KPOP;
      vm->current->ip     = -1;
      vm->current         = vm->current->bound_method;
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
    case_opcode(OP_INCLUDE) {
      next_opcode;
    }
    /* case_opcode(OP_INCLUDE) {
      uint8_t *previous_bytecode = vm->current->bytecode;
      uint8_t *previous_position = vm->current->ip;

      MargValue filename = fs_pop(vm->sp);
      fs_pop(vm->sp);
      vm->filename = AS_STRING(filename)->value;

      EVAL(EMIT(OPTIMIZE(FORMALIZE(READ(LOAD(vm))))));

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
