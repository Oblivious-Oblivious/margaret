#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "vm.h"

/**
 * -- single --
 * O - opcode (8)
 *
 * -- constants --
 * OAk - opcode (8) - operand Ak (24)
 * OABk - opcode (8) - operand A (8) - operand Bk (16)
 *
 * -- commands --
 * OA - opcode (8) - operand A (8)
 * OAB - opcode (8) - operand A (8) - operand B (8)
 * OABC - opcode (8) - operand A (8) - operand B (8) - operand C (8)
 */
#define O(op) vector_add(bc, ((op) << 24))
#define OAk(op, a, k)                               \
  vector_add(                                       \
    bc,                                             \
    (((op) << 24) | (get_register(vm, (a)) << 16) | \
     (vm_make_constant(vm, (k)) & 0x0000ffff))      \
  )
#define OABk(op, a, bk)                             \
  vector_add(                                       \
    bc,                                             \
    (((op) << 24) | (get_register(vm, (a)) << 16) | \
     (vm_make_constant(vm, (bk)) & 0x0000ffff))     \
  )
#define OA(op, a)     vector_add(bc, (((op) << 24) | (get_register(vm, (a)) << 16)))
#define OAB(op, a, b) vector_add(bc, (((op) << 24) | ((a) << 16) | ((b) << 8)))
#define OABC(op, a, b, c)                                         \
  vector_add(                                                     \
    bc,                                                           \
    (((op) << 24) | (get_register(vm, (a)) << 16) |               \
     (get_register(vm, (b)) << 8) | (get_register(vm, (c)) << 0)) \
  )

#define FETCH(i) (((i) & 0xff000000) >> 24)
#define A(i)     (((i) & 0x00ff0000) >> 16)
#define B(i)     (((i) & 0x0000ff00) >> 8)
#define C(i)     (((i) & 0x000000ff) >> 0)
/* TODO - Implement Ak */
#define Bk(i)    ((B(i) << 8) | C(i))

static uint8_t get_register(VM *vm, const char *var) {
  size_t reg_ptr = table_get(&vm->local_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    uint8_t reg = table_size(&vm->local_variables) % MAX_REGISTERS;
    table_add(&vm->local_variables, var, reg);
    return reg;
  }
}

#endif
