#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "vm.h"

/**
 * -- single --
 * O - opcode (16)
 *
 * -- constants --
 * OAk - opcode (16) - operand Ak (48)
 * OABk - opcode (16) - operand A (16) - operand Bk (32)
 *
 * -- commands --
 * OA - opcode (16) - operand A (48)
 * OAB - opcode (16) - operand A (24) - operand B (24)
 * OABC - opcode (16) - operand A (16) - operand B (16) - operand C (16)
 */
#define O(op) vector_add(bc, ((op) << 48))
#define OAk(op, a, k)                                  \
  vector_add(                                          \
    bc,                                                \
    (((op) << 48) | (get_register(vm, (a)) << 32) |    \
     (vm_make_constant(vm, (k)) & 0x00000000ffffffff)) \
  )
#define OABk(op, a, bk)                                 \
  vector_add(                                           \
    bc,                                                 \
    (((op) << 48) | (get_register(vm, (a)) << 32) |     \
     (vm_make_constant(vm, (bk)) & 0x00000000ffffffff)) \
  )
#define OA(op, a)     vector_add(bc, (((op) << 48) | (get_register(vm, (a)) << 32)))
#define OAB(op, a, b) vector_add(bc, (((op) << 48) | ((a) << 32) | ((b) << 16)))
#define OABC(op, a, b, c)                                          \
  vector_add(                                                      \
    bc,                                                            \
    (((op) << 48) | (get_register(vm, (a)) << 32) |                \
     (get_register(vm, (b)) << 16) | (get_register(vm, (c)) << 0)) \
  )

static Instruction get_register(VM *vm, const char *var) {
  Instruction reg_ptr = table_get(&vm->local_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    Instruction reg = table_size(&vm->local_variables) % MAX_REGISTERS;
    table_add(&vm->local_variables, var, reg);
    return reg;
  }
}

#endif
