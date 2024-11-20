#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "object.h"

/**
 * OP   - opcode (6) - rest (58)
 * OA   - opcode (6) - operand A (29) - rest (29)
 * OAB  - opcode (6) - operand A (29) - operand B (29)
 */
#define OP(op)    vector_add(vm->current->bytecode, (op << 58))
#define OA(op, a) vector_add(vm->current->bytecode, (op << 58) | (a << 29))
#define OAB(op, a, b) \
  vector_add(vm->current->bytecode, (op << 58) | (a << 29) | (b << 0))

#define REG_TYPE_LOCAL    (0x00000)
#define REG_TYPE_INSTANCE (0x10000)
#define REG_TYPE_GLOBAL   (0x20000)
#define REG_TYPE_CONSTANT (0x30000)

p_inline Instruction make_constant(VM *vm, MargValue value) {
  size_t k_ptr;
  vector_add(vm->current->constants, value);
  k_ptr = vector_size(vm->current->constants) - 1;
  k_ptr |= REG_TYPE_CONSTANT;
  return k_ptr;
}

p_inline Instruction make_local(VM *vm, const char *var) {
  Instruction reg_ptr = table_get(&vm->current->local_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->current->local_index & (MAX_REGISTERS - 1);
    reg_ptr |= REG_TYPE_LOCAL;
    table_add(&vm->current->local_variables, var, reg_ptr);
    vm->current->local_index++;
    return reg_ptr;
  }
}

p_inline Instruction make_instance(VM *vm, const char *var) {
  Instruction reg_ptr =
    table_get(&vm->current->bound_object->instance_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->current->bound_object->instance_index & (MAX_REGISTERS - 1);
    reg_ptr |= REG_TYPE_INSTANCE;
    table_add(&vm->current->bound_object->instance_variables, var, reg_ptr);
    vm->current->bound_object->instance_index++;
    return reg_ptr;
  }
}

p_inline Instruction make_global(VM *vm, const char *var) {
  Instruction reg_ptr = table_get(&vm->global_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->global_index & (MAX_REGISTERS - 1);
    reg_ptr |= REG_TYPE_GLOBAL;
    table_add(&vm->global_variables, var, reg_ptr);
    vm->global_index++;
    return reg_ptr;
  }
}

#define READ() (vm->current->bytecode[vm->current->ip])

#define GET_TYPE(i)  ((i) & 0x30000)
#define GET_INDEX(i) ((i) & 0x0ffff)

#define IS_LOCAL(i)    (GET_TYPE(i) == REG_TYPE_LOCAL)
#define IS_INSTANCE(i) (GET_TYPE(i) == REG_TYPE_INSTANCE)
#define IS_GLOBAL(i)   (GET_TYPE(i) == REG_TYPE_GLOBAL)
#define IS_CONSTANT(i) (GET_TYPE(i) == REG_TYPE_CONSTANT)

#define GET_K(i) (vm->current->constants[GET_INDEX(i)])
#define GET_L(i) (vm->current->local_registers[GET_INDEX(i)])
#define GET_I(i) (vm->current->bound_object->instance_registers[GET_INDEX(i)])
#define GET_G(i) (vm->global_registers[GET_INDEX(i)])
#define GET_R(i)               \
  (IS_CONSTANT(i)   ? GET_K(i) \
   : IS_LOCAL(i)    ? GET_L(i) \
   : IS_INSTANCE(i) ? GET_I(i) \
   : IS_GLOBAL(i)   ? GET_G(i) \
                    : MARG_UNDEFINED)

#define SET_K(i, v) (GET_K(i) = (v))
#define SET_L(i, v) (GET_L(i) = (v))
#define SET_I(i, v) (GET_I(i) = (v))
#define SET_G(i, v) (GET_G(i) = (v))
#define SET_R(i, v)               \
  (IS_CONSTANT(i)   ? SET_K(i, v) \
   : IS_LOCAL(i)    ? SET_L(i, v) \
   : IS_INSTANCE(i) ? SET_I(i, v) \
   : IS_GLOBAL(i)   ? SET_G(i, v) \
                    : MARG_UNDEFINED)

#define CONST(value)  (make_constant((vm), (value)))
#define LOCAL(var)    (make_local((vm), (var)))
#define INSTANCE(var) (make_instance((vm), (var)))
#define GLOBAL(var)   (make_global((vm), (var)))

#define O    ((READ() >> 58) & 0x3f)
#define A    ((READ() >> 29) & 0x1fffffff)
#define B    ((READ() >> 0) & 0x1fffffff)
#define Z    (vector_size(vm->current->constants) - 1)
#define K(i) (vm->current->constants[(i + Z + 1) % (Z + 1)])
#define L(n) GET_L(table_get(&vm->current->local_variables, (n)))
#define I(n) \
  GET_I(table_get(&vm->current->bound_object->instance_variables, (n)))
#define G(n) GET_G(table_get(&vm->global_variables, (n)))

#define RA GET_R(A)
#define RB GET_R(B)
#define KZ GET_K(Z)

#define SRA(v) SET_R(A, v)
#define SRB(v) SET_R(B, v)
#define SKZ(v) SET_K(Z, v)

#define SG(proto, name) SET_G(GLOBAL(name), MARG_OBJECT(proto, name))

#endif
