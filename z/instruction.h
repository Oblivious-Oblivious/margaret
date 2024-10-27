#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "vm.h"

/**
 * -- single --
 * OP - opcode (16) - rest (48)
 *
 * -- constants --
 * OAk  - opcode (16) - operand Ak (32) - rest (16)
 * OABk - opcode (16) - operand A (16) - operand Bk (32)
 *
 * -- registers --
 * OA   - opcode (16) - operand A (16) - rest (32)
 * OAB  - opcode (16) - operand A (16) - operand B (16) - rest (16)
 * OABC - opcode (16) - operand A (16) - operand B (16) - operand C (16)
 */
#define OP(op)      vector_add(vm->bytecode, ((op) << 48))
#define OAk(op, ak) vector_add(vm->bytecode, ((op) << 48) | (CONST(ak) << 16))
#define OABk(op, a, bk) \
  vector_add(vm->bytecode, ((op) << 48) | (REG(a) << 32) | CONST(bk))
#define OA(op, a) vector_add(vm->bytecode, ((op) << 48) | (REG(a) << 32))
#define OAB(op, a, b) \
  vector_add(vm->bytecode, ((op) << 48) | (REG(a) << 32) | (REG(b) << 16))
#define OABC(op, a, b, c)                                          \
  vector_add(                                                      \
    vm->bytecode,                                                  \
    ((op) << 48) | (REG(a) << 32) | (REG(b) << 16) | (REG(c) << 0) \
  )

#define CONST(value) (make_constant((vm), (value)))
#define REG(var)     (make_register((vm), (var)))

p_inline Instruction make_constant(VM *vm, Value value) {
  vector_add(vm->constants, value);
  return vector_size(vm->constants) - 1;
}
p_inline Instruction make_register(VM *vm, const char *var) {
  Instruction reg_ptr = table_get(&vm->local_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    Instruction reg = table_size(&vm->local_variables) & (MAX_REGISTERS - 1);
    table_add(&vm->local_variables, var, reg);
    return reg;
  }
}

#define READ() (vm->bytecode[vm->ip - 1])

#define R(i) (vm->registers[i])
#define K(i) (vm->constants[i])

#define O  (uint16_t)((READ() & 0xffff000000000000) >> 48)
#define A  (uint16_t)((READ() & 0x0000ffff00000000) >> 32)
#define B  (uint16_t)((READ() & 0x00000000ffff0000) >> 16)
#define C  (uint16_t)((READ() & 0x000000000000ffff) >> 0)
#define Ak (uint32_t)((READ() & 0x0000ffffffff0000) >> 16)
#define Bk (uint32_t)((READ() & 0x00000000ffffffff) >> 0)

#define RA  R(A)
#define RB  R(B)
#define RC  R(C)
#define KAk K(Ak)
#define KBk K(Bk)

#endif
