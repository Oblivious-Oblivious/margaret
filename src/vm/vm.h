#ifndef __VM_H_
#define __VM_H_

#include <stdint.h>
#include "../base/vector.h"
#include "../base/memory.h"
#include "../base/chunk.h"
#include "../base/table.h"
#include "../opcode/MargValue.h"
#include "byte_conversions.h"

/**
 * @brief Virtual Machine Engine
 * @param bytecode -> The list of emitted bytecode instructions
 * @param ip -> Instruction pointer that directly points into bytecode array
 */
typedef struct VM {
    // TODO Refactor Chunk for space locality
    chunk *bytecode;
    uint8_t *ip;

    MargValue stack[65536];
    MargValue *sp;

    table interned_strings;
    table global_variables;
} VM;

/** @brief Better assurances for inlining */
#define inline __inline__

inline void STACK_PUSH(VM *self, MargValue item) {
    *self->sp++ = item;
}

inline MargValue STACK_POP(VM *self) {
    return *--self->sp;
}

inline MargValue STACK_PEEK(VM *self, int distance) {
    return *(self->sp - 1 - distance);
}

#define READ_BYTE() (*self->ip++)
#define READ_WORD() (bytes_to_word((uint8_t[2]){READ_BYTE(), READ_BYTE()}))
#define READ_DWORD() (bytes_to_dword((uint8_t[4]){READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE()}))
#define READ_QWORD() (bytes_to_qword((uint8_t[8]){READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE()}))

#define READ_TEMPORARY() (chunk_temporaries_get(self->bytecode, READ_BYTE()))
#define READ_LONG_TEMPORARY() (chunk_temporaries_get(self->bytecode, READ_DWORD()))

/**
 * @brief Creates a new VM instance
        By being an explicit pointer can create multiple of them
 * @return VM* 
 */
VM *vm_new(void);

/**
 * @brief Explicitely frees VM memory that is kept outside of the collector
        Memory critical sections like temporaries are kept outside of the GC
 * @param vm -> Current vm
 */
void vm_free(VM *vm);

#endif
