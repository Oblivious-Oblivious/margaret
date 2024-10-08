#ifndef __VM_H_
#define __VM_H_

#define TABLE_UNDEFINED MARG_UNDEFINED
#include "../../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "../opcode/MargValueType.h"
#include "../tokens/Tokens.h"
#include "byte_conversions.h"

#include <stdint.h> /* uint8_t */

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
 * @param global_variables -> Global without namespacing or scoping
 * @param interned_strings -> Stores all strings (variables, messages, etc.)
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

  /* TODO - Remove */
  MargValue stack[65536];
  MargValue *sp;

  EmeraldsTable global_variables;
  EmeraldsTable interned_strings;
  struct MargProc *current;
} VM;

/** @brief Works for any IP pointer no matter what context current is in */
#define READ_BYTE() (*vm->current->ip++)
#define READ_WORD() (bytes_to_word(READ_BYTE(), READ_BYTE()))
#define READ_DWORD() \
  (bytes_to_dword(READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE()))

#define READ_TEMPORARY()       (vm->current->bytecode[READ_BYTE()])
#define READ_TEMPORARY_WORD()  (vm->current->bytecode[READ_WORD()])
#define READ_TEMPORARY_DWORD() (vm->current->bytecode[READ_DWORD()])

/**
 * @brief Creates a new VM instance By being an explicit pointer can create
 * multiple of them
 * @param filename -> Current filename to lex tokens from
 * @return VM*
 */
VM *vm_new(const char *filename);

/**
 * @brief Frees the VM instance.  Most of its values are freed over time by
 * other parts of the pipeline.  This handles remaining fields
 * @param vm -> The VM to be freed
 */
#define vm_free()                        \
  do {                                   \
    vm_free_source();                    \
    vm_free_tokens();                    \
    vm_free_formal_bytecode();           \
    table_deinit(&vm->global_variables); \
    table_deinit(&vm->interned_strings); \
    free(vm);                            \
  } while(0)

/* TODO - Ensure there are no leaks throughout the pipeline */
#ifndef MARG_SPEC
  #define vm_free_source() string_free(vm->source)

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
    } while(0)

#else
  #define vm_free_source()
  #define vm_free_tokens()
  #define vm_free_formal_bytecode()
#endif

#endif
