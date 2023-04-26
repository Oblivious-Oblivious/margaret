#ifndef __VM_H_
#define __VM_H_

#include <stdint.h>
#include "../base/vector.h"
#include "../base/memory.h"
#include "../opcode/MargValue.h"
#include "../opcode/MargHash.h"

/**
 * @brief Virtual Machine Engine
 * @param bytecode -> The list of emitted bytecode instructions
 * @param ip -> Instruction pointer that directly points into bytecode array
 */
typedef struct VM {
    // TODO Refactor Chunk for space locality
    Chunk *bytecode;
    uint8_t *ip;

    MargValue stack[65536];
    MargValue *stack_top;

    MargHash interned_strings;
    MargHash global_variables;
    MargHash string_constants;
} VM;

/** @brief Better assurances for inlining */
#define inline __inline__

inline void STACK_PUSH(VM *self, MargValue item) {
    *self->stack_top++ = item;
}

inline MargValue STACK_POP(VM *self) {
    return *--self->stack_top;
}

inline MargValue STACK_PEEK(VM *self, int distance) {
    return *(self->stack_top - 1 - distance);
}

#define READ_BYTE() (*self->ip++)
#define READ_CONSTANT() (self->bytecode->constants->items[READ_BYTE()])
#define READ_LONG_CONSTANT() (self->bytecode->constants->items[bytes_to_long_constant((uint8_t[4]){READ_BYTE(), READ_BYTE(), READ_BYTE(), READ_BYTE()})])
#define READ_STRING() AS_STRING(READ_CONSTANT())
#define READ_LONG_STRING() AS_STRING(READ_LONG_CONSTANT())

VM *vm_new(void);

#endif
