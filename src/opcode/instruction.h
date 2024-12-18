#ifndef __INSTRUCTION_H_
#define __INSTRUCTION_H_

#include "MargValue.h"

/**
 * OP   - opcode (6) - rest (58)
 * OA   - opcode (6) - operand A (29) - rest (29)
 * OAB  - opcode (6) - operand A (29) - operand B (29)
 */
#define OP(op)    vector_add(vm->current->bytecode, (op << 58))
#define OA(op, a) vector_add(vm->current->bytecode, (op << 58) | (a << 29))
#define OAB(op, a, b) \
  vector_add(vm->current->bytecode, (op << 58) | (a << 29) | (b << 0))

p_inline Instruction make_constant(VM *vm, MargValue value) {
  vector_add(vm->current->constants, value);
  return vector_size(vm->current->constants) - 1;
}

p_inline Instruction make_local(VM *vm, const char *_var) {
  const char *var     = string_new(_var);
  Instruction reg_ptr = table_get(&vm->current->local_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->current->local_index & (MAX_REGISTERS - 1);
    table_add(&vm->current->local_variables, var, reg_ptr);
    vm->current->local_registers[reg_ptr] =
      MARG_VARIABLE(var, vm->current->local_registers[reg_ptr], VAR_TYPE_LOCAL);
    vm->current->local_index++;
    return reg_ptr;
  }
}

p_inline Instruction make_instance(VM *vm, const char *_var) {
  const char *var = string_new(_var);
  Instruction reg_ptr =
    table_get(&vm->current->bound_object->instance_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->current->bound_object->instance_index & (MAX_REGISTERS - 1);
    table_add(&vm->current->bound_object->instance_variables, var, reg_ptr);
    vm->current->bound_object->instance_registers[reg_ptr] = MARG_VARIABLE(
      var,
      vm->current->bound_object->instance_registers[reg_ptr],
      VAR_TYPE_INSTANCE
    );
    vm->current->bound_object->instance_index++;
    return reg_ptr;
  }
}

p_inline Instruction make_global(VM *vm, const char *_var) {
  const char *var     = string_new(_var);
  Instruction reg_ptr = table_get(&vm->global_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->global_index & (MAX_REGISTERS - 1);
    table_add(&vm->global_variables, var, reg_ptr);
    vm->global_registers[reg_ptr] =
      MARG_VARIABLE(var, vm->global_registers[reg_ptr], VAR_TYPE_GLOBAL);
    vm->global_index++;
    return reg_ptr;
  }
}

p_inline Instruction make_global_singleton(VM *vm, const char *var) {
  Instruction reg_ptr = table_get(&vm->global_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    reg_ptr = vm->global_index & (MAX_REGISTERS - 1);
    table_add(&vm->global_variables, var, reg_ptr);
    vm->global_index++;
    return reg_ptr;
  }
}

#define READ_BYTECODE() (vm->current->bytecode[vm->current->ip])

#define GET_K(i) (vm->current->constants[(i)])
#define GET_L(i) (vm->current->local_registers[(i)])
#define GET_I(i) (vm->current->bound_object->instance_registers[(i)])
#define GET_G(i) (vm->global_registers[(i)])

#define SET_K(i, v) (GET_K(i) = (v))
#define SET_L(i, v) (GET_L(i) = (v))
#define SET_I(i, v) (GET_I(i) = (v))
#define SET_G(i, v) (GET_G(i) = (v))

#define CONST(value)          (make_constant((vm), (value)))
#define LOCAL(var)            (make_local((vm), (var)))
#define INSTANCE(var)         (make_instance((vm), (var)))
#define GLOBAL(var)           (make_global((vm), (var)))
#define GLOBAL_SINGLETON(var) (make_global_singleton((vm), (var)))

#define O    ((READ_BYTECODE() >> 58) & 0x3f)
#define A    ((READ_BYTECODE() >> 29) & 0x1fffffff)
#define B    ((READ_BYTECODE() >> 0) & 0x1fffffff)
#define Z    (vector_size(vm->current->constants) - 1)
/* TODO - Probably replace in the future */
#define K(i) (vm->current->constants[(i + Z + 1) % (Z + 1)])

/* TODO - Optimize by calling only once */
#define L(n)                                                   \
  (IS_UNDEFINED(table_get(&vm->current->local_variables, (n))) \
     ? GET_G(table_get(&vm->global_variables, "$nil"))         \
     : GET_L(table_get(&vm->current->local_variables, (n))))
#define I(n)                                                                   \
  (IS_UNDEFINED(table_get(&vm->current->bound_object->instance_variables, (n)) \
   )                                                                           \
     ? GET_G(table_get(&vm->global_variables, "$nil"))                         \
     : GET_I(table_get(&vm->current->bound_object->instance_variables, (n))))
#define G(n)                                           \
  (IS_UNDEFINED(table_get(&vm->global_variables, (n))) \
     ? GET_G(table_get(&vm->global_variables, "$nil")) \
     : GET_G(table_get(&vm->global_variables, (n))))

#define KA GET_K(A)
#define LA GET_L(A)
#define IA GET_I(A)
#define GA GET_G(A)

#define KB GET_K(B)
#define LB GET_L(B)
#define IB GET_I(B)
#define GB GET_G(B)

#define KPUSH(i) (vector_push(vm->current->constants, (i)))
#define KPOP     (vector_pop(vm->current->constants))
#define KZ       (vector_peek(vm->current->constants))

#define SLA(v) SET_L(A, v)
#define SIA(v) SET_I(A, v)
#define SGA(v) SET_G(A, v)

#define SLB(v) SET_L(B, v)
#define SIB(v) SET_I(B, v)
#define SGB(v) SET_G(B, v)

#define SKZ(v) SET_K(Z, v)

#define SG(proto, name) SET_G(GLOBAL_SINGLETON(name), MARG_OBJECT(proto, name))

#endif
