#ifndef __VM_H_
#define __VM_H_

#include "../base/memory.h"
#include "../base/table.h"
#include "../opcode/MargValueType.h"
#include "byte_conversions.h"

#include <stdint.h> /* uint8_t */

typedef struct MargProc MargProc;

/**
 * @brief Virtual Machine Engine
 * @param bytecode -> The list of emitted bytecode instructions
 * @param ip -> Instruction pointer that directly points into bytecode array
 */
typedef struct VM {
  MargValue stack[65536];
  MargValue *sp;
  table global_variables;
  table interned_strings;
  MargProc *current;
} VM;

/** @brief Works for any IP pointer no matter what context current is in */
#define READ_BYTE() (*vm->current->ip++)
#define READ_WORD() (bytes_to_word((uint8_t[2]){READ_BYTE(), READ_BYTE()}))
#define READ_DWORD()          \
  (bytes_to_dword((uint8_t[4] \
  ){READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE()}))

#define READ_TEMPORARY()       (vm->current->bytecode[READ_BYTE()])
#define READ_TEMPORARY_WORD()  (vm->current->bytecode[READ_WORD()])
#define READ_TEMPORARY_DWORD() (vm->current->bytecode[READ_DWORD()])

/**
 * @brief Creates a new VM instance
        By being an explicit pointer can create multiple of them
 * @return VM*
 */
VM *vm_new(void);

#endif
