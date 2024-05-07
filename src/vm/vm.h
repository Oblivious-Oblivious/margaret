#ifndef __VM_H_
#define __VM_H_

#include <stdint.h> /* uint8_t */

#include "../base/vector.h"
#include "../base/memory.h"
#include "../base/chunk.h"
#include "../base/table.h"
#include "../opcode/MargValueType.h"
#include "byte_conversions.h"

// #include "../opcode/MargProc.h"
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

/** @brief Better assurances for inlining */
#define inline __inline__

inline void STACK_PUSH(VM *vm, MargValue item) {
    *vm->sp++ = item;
}

inline MargValue STACK_POP(VM *vm) {
    return *--vm->sp;
}

inline MargValue STACK_PEEK(VM *vm, int distance) {
    return *(vm->sp - 1 - distance);
}

/** @brief Works for any IP pointer no matter what context current is in */
#define READ_BYTE() (*vm->current->ip++)
#define READ_WORD() (bytes_to_word((uint8_t[2]){READ_BYTE(), READ_BYTE()}))
#define READ_DWORD() (bytes_to_dword((uint8_t[4]){READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE()}))

#define READ_TEMPORARY() (chunk_temporaries_get(vm->current->bytecode, READ_BYTE()))
#define READ_TEMPORARY_WORD() (chunk_temporaries_get(vm->current->bytecode, READ_WORD()))
#define READ_TEMPORARY_DWORD() (chunk_temporaries_get(vm->current->bytecode, READ_DWORD()))

/**
 * @brief Creates a new VM instance
        By being an explicit pointer can create multiple of them
 * @return VM* 
 */
VM *vm_new(void);

#endif
