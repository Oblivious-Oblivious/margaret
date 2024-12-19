#ifndef __VM_H_
#define __VM_H_

#include "../opcode/MargValueType.h"

#define TABLE_UNDEFINED MARG_UNDEFINED
#include "../../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "../tokens/Tokens.h"

/**
 * @brief Virtual Machine Engine
 * @param filename -> Current filename to lex tokens from
 * @param source -> Source code read from file
 * @param lineno -> Current line number
 * @param charno -> Current character number
 * @param error -> Stores the latest error message found during the pipeline
 * @param error_token -> Stores the latest error token found during the pipeline
 *
 * @param tid -> Current token index
 * @param tokens -> List of tokenized values
 * @param formal_bytecode -> Formal bytecode representation
 *
 * @param global_registers -> Global register array
 * @param global_index -> Global register index
 * @param global_variables -> Global without namespacing or scoping
 * @param primitives -> List of primitives
 * @param current -> Pointer to the currect method-derived proc
 */
typedef struct VM {
  const char *filename;
  char *source;
  size_t lineno;
  size_t charno;
  const char *error;
  const char *error_token;

  size_t tid;
  Tokens tokens;
  char **formal_bytecode;

  MargValue global_registers[MAX_REGISTERS];
  uint32_t global_index;
  EmeraldsTable global_variables;
  EmeraldsTable primitives;
  struct MargMethod *current;
  bool do_not_display;
} VM;

/* TODO - Refactor vm to a stack-bound value with vm_new(&vm, "repl") */
/**
 * @brief Creates a new VM instance By being an explicit pointer can create
 * multiple of them
 * @param filename -> Current filename to lex tokens from
 * @return VM*
 */
VM *vm_new(const char *filename);

/**
 * @brief Resets the VM instance.  Most of its values are freed over time by
 * other parts of the pipeline.  This handles remaining fields
 * @param vm -> The VM to be reset
 */
#define vm_reset()                 \
  do {                             \
    vm_free_source();              \
    vm->error       = NULL;        \
    vm->error_token = NULL;        \
    vm_free_tokens();              \
    tokens_init(&vm->tokens);      \
    vm_free_formal_bytecode();     \
    vm->current->ip       = -1;    \
    vm->current->bytecode = NULL;  \
    vm->do_not_display    = false; \
  } while(0)

/* TODO - Ensure there are no leaks throughout the pipeline */
#define vm_free_source()     \
  do {                       \
    string_free(vm->source); \
    vm->source = NULL;       \
    vm->lineno = 1;          \
    vm->charno = 0;          \
  } while(0)

#define vm_free_tokens()        \
  do {                          \
    tokens_deinit(&vm->tokens); \
    vm->tid = 0;                \
  } while(0)

#define vm_free_formal_bytecode()                           \
  do {                                                      \
    size_t i;                                               \
    for(i = 0; i < vector_size(vm->formal_bytecode); i++) { \
      if(!string_equals(vm->formal_bytecode[i], "eof")) {   \
        string_free(vm->formal_bytecode[i]);                \
      }                                                     \
    }                                                       \
    vector_free(vm->formal_bytecode);                       \
    vm->formal_bytecode = NULL;                             \
  } while(0)

#endif
