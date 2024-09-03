#ifndef __VM_H_
#define __VM_H_

#include "../../libs/EmeraldsHashtable/export/EmeraldsHashtable.h"
#include "../opcode/MargValueType.h"
#include "../tokens/Token.h"
#include "byte_conversions.h"

#include <stdint.h> /* uint8_t */

typedef struct MargProc MargProc;

/**
 * @brief Virtual Machine Engine
 * @param filename -> Current filename to lex tokens from
 * @param source -> Source code read from file
 * @param lineno -> Current line number
 * @param charno -> Current character number
 *
 * @param tokens -> List of tokenized values
 * @param formal_bytecode -> Formal bytecode representation
 *
 * @param stack -> Stack data structure for storing bytecode results
 * @param sp -> Stack pointer
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
  bool has_error;

  Token *eof_token;
  Token **tokens;
  char **formal_bytecode;

  MargValue stack[65536];
  MargValue *sp;

  EmeraldsHashtable global_variables;
  EmeraldsHashtable interned_strings;
  MargProc *current;
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
void vm_free(VM *vm);

#endif
