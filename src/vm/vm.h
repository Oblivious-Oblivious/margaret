#ifndef __VM_H_
#define __VM_H_

#include <stdint.h>
#include "../base/marg_vector.h"
#include "../base/memory.h"
#include "../opcode/MargValue.h"

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
} VM;

inline void STACK_RESET(VM *self) {
    self->stack_top = self->stack;
}

inline void STACK_PUSH(VM *self, MargValue item) {
    *self->stack_top++ = item;
}

inline MargValue STACK_POP(VM *self) {
    return --*self->stack_top;
}

inline MargValue STACK_PEEK(VM *self) {
    return *self->stack_top;
}

#define READ_BYTE() (*self->ip++)
#define READ_CONSTANT() (self->bytecode->constants->items[READ_BYTE()])

VM *vm_new(void);

#endif
