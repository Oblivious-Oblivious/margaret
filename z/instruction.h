#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "vm.h"

/**
 * OP   - opcode (10) - rest (54)
 * OA   - opcode (10) - operand A (18) - rest (36)
 * OAB  - opcode (10) - operand A (18) - operand B (18) - rest (18)
 * OABC - opcode (10) - operand A (18) - operand B (18) - operand C (18)
 */
#define OP(op)    vector_add(vm->bytecode, (op << 54))
#define OA(op, a) vector_add(vm->bytecode, (op << 54) | (a << 36))
#define OAB(op, a, b) \
  vector_add(vm->bytecode, (op << 54) | (a << 36) | (b << 18))
#define OABC(op, a, b, c) \
  vector_add(vm->bytecode, (op << 54) | (a << 36) | (b << 18) | (c << 0))

typedef enum RegisterType {
  REG_TYPE_LOCAL    = 0x00000,
  REG_TYPE_INSTANCE = 0x10000,
  REG_TYPE_GLOBAL   = 0x20000,
  REG_TYPE_CONSTANT = 0x30000
} RegisterType;

p_inline Instruction make_constant(VM *vm, Value value) {
  vector_add(vm->constants, value);
  return (vector_size(vm->constants) - 1) | REG_TYPE_CONSTANT;
}

p_inline Instruction make_register(VM *vm, const char *var, RegisterType type) {
  EmeraldsTable *table = NULL;
  size_t max_size;
  Instruction reg_ptr;

  if(type == REG_TYPE_LOCAL) {
    table    = &vm->local_variables;
    max_size = MAX_LOCALS;
  } else if(type == REG_TYPE_INSTANCE) {
    table    = &vm->instance_variables;
    max_size = MAX_INSTANCES;
  } else if(type == REG_TYPE_GLOBAL) {
    table    = &vm->global_variables;
    max_size = MAX_GLOBALS;
  }

  reg_ptr = table_get(table, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr | type;
  } else {
    reg_ptr = table_size(table) & (max_size - 1);
    table_add(table, var, reg_ptr);
    return reg_ptr | type;
  }
}

#define READ() (vm->bytecode[vm->ip])

#define GET_TYPE(i)  ((i) & 0x30000)
#define GET_INDEX(i) ((i) & 0x0FFFF)

#define IS_LOCAL(i)    (GET_TYPE(i) == REG_TYPE_LOCAL)
#define IS_INSTANCE(i) (GET_TYPE(i) == REG_TYPE_INSTANCE)
#define IS_GLOBAL(i)   (GET_TYPE(i) == REG_TYPE_GLOBAL)
#define IS_CONSTANT(i) (GET_TYPE(i) == REG_TYPE_CONSTANT)

#define GET_R(i)                                  \
  (IS_LOCAL(i)      ? vm->locals[GET_INDEX(i)]    \
   : IS_INSTANCE(i) ? vm->instances[GET_INDEX(i)] \
   : IS_GLOBAL(i)   ? vm->globals[GET_INDEX(i)]   \
   : IS_CONSTANT(i) ? vm->constants[GET_INDEX(i)] \
                    : 0)

#define SET_R(i, v)                                       \
  (IS_LOCAL(i)      ? (vm->locals[GET_INDEX(i)] = (v))    \
   : IS_INSTANCE(i) ? (vm->instances[GET_INDEX(i)] = (v)) \
   : IS_GLOBAL(i)   ? (vm->globals[GET_INDEX(i)] = (v))   \
   : IS_CONSTANT(i) ? (vector_add(vm->constants, v))      \
                    : 0)

#define CONST(value)  (make_constant((vm), (value)))
#define LOCAL(var)    (make_register((vm), (var), REG_TYPE_LOCAL))
#define INSTANCE(var) (make_register((vm), (var), REG_TYPE_INSTANCE))
#define GLOBAL(var)   (make_register((vm), (var), REG_TYPE_GLOBAL))

#define O ((READ() >> 54) & 0x3ff)
#define A ((READ() >> 36) & 0x3ffff)
#define B ((READ() >> 18) & 0x3ffff)
#define C ((READ() >> 0) & 0x3ffff)

#define RA GET_R(A)
#define RB GET_R(B)
#define RC GET_R(C)

#define SRA(v) SET_R(A, v)
#define SRB(v) SET_R(B, v)
#define SRC(v) SET_R(C, v)

#endif
