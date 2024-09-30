#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "../libs/EmeraldsVector/export/EmeraldsVector.h"

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

#define OP_NIL           0x00
#define OP_FALSE         0x01
#define OP_TRUE          0x02
#define OP_NUMBER        0x03
#define OP_STRING        0x04
#define OP_ADD           0x05
#define OP_SUB           0x06
#define OP_MUL           0x07
#define OP_DIV           0x08
#define OP_JUMP          0x09
#define OP_JUMP_IF_FALSE 0x0a
#define OP_PRINT         0x0b
#define OP_HALT          0x0c

typedef uint8_t Type;

#define TYPE_NIL    0x00
#define TYPE_FALSE  0x01
#define TYPE_TRUE   0x02
#define TYPE_NUMBER 0x03
#define TYPE_STRING 0x04

/** @brief Ex nihilo value */
typedef size_t Value;

/** QNAN = 0b    0     11111111111       1            1       ('0' * 50)
              (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest) */
#define SIGN_BIT  ((size_t)0x8000000000000000)
#define EXPONENTS ((size_t)0x7ff0000000000000)
#define QNAN      ((size_t)0x0008000000000000)
#define FP_IND    ((size_t)0x0004000000000000)
#define ENCODING  (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer) ((Value)(ENCODING | (size_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value) ((Object *)(uintptr_t)((value) & ~(ENCODING)))

#define NIL()         (QNAN_BOX(value_nil_new(vm)))
#define FALSE()       (QNAN_BOX(value_false_new(vm)))
#define TRUE()        (QNAN_BOX(value_true_new(vm)))
#define NUMBER(value) (QNAN_BOX(value_number_new(vm, (value))))
#define STRING(value) (QNAN_BOX(value_string_new(vm, string_new((value)))))

#define AS_NIL(value)    ((Nil *)QNAN_UNBOX(value))
#define AS_FALSE(value)  ((False *)QNAN_UNBOX(value))
#define AS_TRUE(value)   ((True *)QNAN_UNBOX(value))
#define AS_NUMBER(value) ((Number *)QNAN_UNBOX(value))
#define AS_STRING(value) ((String *)QNAN_UNBOX(value))
#define AS_OBJECT(value) ((Object *)QNAN_UNBOX(value))

#define IS_NIL(value)    (AS_OBJECT(value)->type == TYPE_NIL)
#define IS_FALSE(value)  (AS_OBJECT(value)->type == TYPE_FALSE)
#define IS_TRUE(value)   (AS_OBJECT(value)->type == TYPE_TRUE)
#define IS_NUMBER(value) (AS_OBJECT(value)->type == TYPE_NUMBER)
#define IS_STRING(value) (AS_OBJECT(value)->type == TYPE_STRING)

#define MAX_REGISTERS (2 << 7)
#define MAX_CONSTANTS (2 << 7)

typedef struct {
  uint8_t operands[4];
} Instruction;

typedef struct {
  Value registers[MAX_REGISTERS];
  Value constants[MAX_CONSTANTS];
  uint8_t num_constants;
  size_t ip;
  Instruction **bytecode;
} VM;

typedef struct Object {
  bool is_marked;
  Type type;
  struct Object *next;
} Object;

Object *value_object_new(VM *bound_vm, size_t size, Type type) {
  Object *self = (Object *)malloc(sizeof(Object) * size);

  self->is_marked = false;
  self->type      = type;
  self->next      = NULL;

  return self;
}

typedef struct Nil {
  Object _;
} Nil;

Nil *value_nil_new(VM *vm) {
  Object *obj = (Object *)value_object_new(vm, sizeof(Nil), TYPE_NIL);
  Nil *self   = (Nil *)obj;

  return self;
}

typedef struct False {
  Object _;
} False;

False *value_false_new(VM *vm) {
  Object *obj = (Object *)value_object_new(vm, sizeof(False), TYPE_FALSE);
  False *self = (False *)obj;

  return self;
}

typedef struct True {
  Object _;
} True;

True *value_true_new(VM *vm) {
  Object *obj = (Object *)value_object_new(vm, sizeof(True), TYPE_TRUE);
  True *self  = (True *)obj;

  return self;
}

typedef struct Number {
  Object _;

  double value;
} Number;

Number *value_number_new(VM *vm, double value) {
  Object *obj  = (Object *)value_object_new(vm, sizeof(Number), TYPE_NUMBER);
  Number *self = (Number *)obj;

  self->value = value;

  return self;
}

typedef struct String {
  Object _;
  char *value;
} String;

String *value_string_new(VM *vm, char *chars) {
  size_t size = string_size(chars);
  Object *obj =
    (Object *)value_object_new(vm, sizeof(String) + size + 1, TYPE_STRING);
  String *self = (String *)obj;

  self->value = chars;

  return self;
}

Instruction *
instruction_new(uint8_t opcode, uint8_t op1, uint8_t op2, uint8_t op3) {
  Instruction *i = (Instruction *)malloc(sizeof(Instruction));

  i->operands[0] = opcode;
  i->operands[1] = op1;
  i->operands[2] = op2;
  i->operands[3] = op3;

  return i;
}

void vm_init(VM *vm, Instruction **bytecode) {
  vm->num_constants = 0;
  vm->bytecode      = bytecode;
  vm->ip            = 0;
}

uint8_t make_constant(VM *vm, Value value) {
  vm->constants[vm->num_constants++] = value;
  return vm->num_constants - 1;
}

void vm_execute(VM *vm) {
#if defined(__GNUC__) || defined(__clang__)
  static void *_computed_gotos[] = {
    &&_computed_goto_OP_NIL,
    &&_computed_goto_OP_FALSE,
    &&_computed_goto_OP_TRUE,
    &&_computed_goto_OP_NUMBER,
    &&_computed_goto_OP_STRING,
    &&_computed_goto_OP_ADD,
    &&_computed_goto_OP_SUB,
    &&_computed_goto_OP_MUL,
    &&_computed_goto_OP_DIV,
    &&_computed_goto_OP_JUMP,
    &&_computed_goto_OP_JUMP_IF_FALSE,
    &&_computed_goto_OP_PRINT,
    &&_computed_goto_OP_HALT
  };
  #define switch_opcode                    \
    Instruction *i = vm->bytecode[vm->ip]; \
    goto *_computed_gotos[i->operands[0]];
  #define case_opcode(op) _computed_goto_##op:
  #define default_opcode \
  _err:
  #define next_opcode         \
    vm->ip++;                 \
    i = vm->bytecode[vm->ip]; \
    goto *_computed_gotos[i->operands[0]]
  #define skip_opcode goto *_computed_gotos[i->operands[0]]
#else
  #define switch_opcode       \
    Instruction *i;           \
  _opcode_loop:               \
    i = vm->bytecode[vm->ip]; \
    switch(i->operands[0])
  #define case_opcode(op) case((op)):
  #define default_opcode  default:
  #define next_opcode \
    vm->ip++;         \
    goto _opcode_loop
  #define skip_opcode goto _opcode_loop
#endif

  switch_opcode {
    case_opcode(OP_NIL) {
      vm->registers[i->operands[1]] = NIL();
      next_opcode;
    }
    case_opcode(OP_FALSE) {
      vm->registers[i->operands[1]] = FALSE();
      next_opcode;
    }
    case_opcode(OP_TRUE) {
      vm->registers[i->operands[1]] = TRUE();
      next_opcode;
    }
    case_opcode(OP_NUMBER) {
      vm->registers[i->operands[1]] = vm->constants[i->operands[2]];
      next_opcode;
    }
    case_opcode(OP_STRING) {
      vm->registers[i->operands[1]] = vm->constants[i->operands[2]];
      next_opcode;
    }
    case_opcode(OP_ADD) {
      vm->registers[i->operands[1]] = NUMBER(
        AS_NUMBER(vm->registers[i->operands[2]])->value +
        AS_NUMBER(vm->registers[i->operands[3]])->value
      );
    }
    next_opcode;
  }
  case_opcode(OP_SUB) {
    vm->registers[i->operands[1]] = NUMBER(
      AS_NUMBER(vm->registers[i->operands[2]])->value -
      AS_NUMBER(vm->registers[i->operands[3]])->value
    );
    next_opcode;
  }
  case_opcode(OP_MUL) {
    vm->registers[i->operands[1]] = NUMBER(
      AS_NUMBER(vm->registers[i->operands[2]])->value *
      AS_NUMBER(vm->registers[i->operands[3]])->value
    );
    next_opcode;
  }
  case_opcode(OP_DIV) {
    if(AS_NUMBER(vm->registers[i->operands[3]])->value == 0.0) {
      fprintf(stderr, "Runtime Error: Division by zero\n");
      exit(1);
    }
    vm->registers[i->operands[1]] = NUMBER(
      AS_NUMBER(vm->registers[i->operands[2]])->value /
      AS_NUMBER(vm->registers[i->operands[3]])->value
    );
    next_opcode;
  }
  case_opcode(OP_JUMP) {
    uint8_t target = i->operands[1];
    if(target >= vector_size(vm->bytecode)) {
      fprintf(stderr, "Invalid jump target: %d\n", target);
      exit(1);
    }
    vm->ip = target;
    skip_opcode;
  }
  case_opcode(OP_JUMP_IF_FALSE) {
    uint8_t condition = vm->registers[i->operands[1]];
    uint8_t target    = i->operands[2];
    if(!condition) {
      if(target >= vector_size(vm->bytecode)) {
        fprintf(stderr, "Invalid jump target: %d\n", target);
        exit(1);
      }
      vm->ip = target;
      skip_opcode;
    } else {
      next_opcode;
    }
  }
  case_opcode(OP_PRINT) {
    Value v = vm->registers[i->operands[1]];
    if(IS_NIL(v)) {
      printf("R%d = nil\n", i->operands[1]);
    } else if(IS_FALSE(v)) {
      printf("R%d = false\n", i->operands[1]);
    } else if(IS_TRUE(v)) {
      printf("R%d = true\n", i->operands[1]);
    } else if(IS_NUMBER(v)) {
      printf("R%d = %g\n", i->operands[1], AS_NUMBER(v)->value);
    } else if(IS_STRING(v)) {
      printf("R%d = \"%s\"\n", i->operands[1], AS_STRING(v)->value);
    } else {
      printf("R%d = UNKNOWN\n", i->operands[1]);
    }
    next_opcode;
  }
  case_opcode(OP_HALT) {
    printf("HALT: Stopping VM execution.\n");
    exit(0);
  }
  default_opcode {
    fprintf(stderr, "Unknown opcode: %d\n", i->operands[0]);
    exit(1);
  }
}

uint8_t
get_register(EmeraldsTable *map, uint8_t *current_reg_ptr, const char *var) {
  size_t reg_ptr = table_get(map, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    uint8_t reg = *current_reg_ptr;
    table_add(map, var, reg);
    *current_reg_ptr = (*current_reg_ptr % MAX_REGISTERS) + 1;
    return reg;
  }
}

#define emit(i)        vector_add(bc, i)
#define emit_0(opcode) emit(instruction_new((opcode), 0, 0, 0));
#define emit_1(opcode, op1)                                    \
  emit(instruction_new(                                        \
    (opcode), get_register(&registers, &next_reg, (op1)), 0, 0 \
  ))
#define emit_2(opcode, op1, op2)                \
  emit(instruction_new(                         \
    (opcode),                                   \
    get_register(&registers, &next_reg, (op1)), \
    get_register(&registers, &next_reg, (op2)), \
    0                                           \
  ))
#define emit_3(opcode, op1, op2, op3)           \
  emit(instruction_new(                         \
    (opcode),                                   \
    get_register(&registers, &next_reg, (op1)), \
    get_register(&registers, &next_reg, (op2)), \
    get_register(&registers, &next_reg, (op3))  \
  ))
#define emit_k(opcode, op1, op2)                                   \
  emit(instruction_new(                                            \
    (opcode), get_register(&registers, &next_reg, (op1)), (op2), 0 \
  ));

#define emit_example_bytecode()                                   \
  do {                                                            \
    emit_k(OP_NIL, "x", make_constant(vm, NIL()));                \
    emit_k(OP_FALSE, "y", make_constant(vm, FALSE()));            \
    emit_k(OP_TRUE, "y2", make_constant(vm, TRUE()));             \
    emit_k(OP_NUMBER, "y3", make_constant(vm, NUMBER(1)));        \
    emit_k(OP_NUMBER, "z", make_constant(vm, NUMBER(10)));        \
    emit_k(OP_NUMBER, "a", make_constant(vm, NUMBER(3.14)));      \
    emit_k(OP_STRING, "msg", make_constant(vm, STRING("Hello"))); \
    emit_3(OP_ADD, "result_add", "z", "a");                       \
    emit_3(OP_SUB, "result_sub", "result_add", "y3");             \
    emit_3(OP_MUL, "result_mul", "result_sub", "z");              \
    emit_3(OP_DIV, "result_div", "result_mul", "a");              \
    emit_1(OP_PRINT, "x");                                        \
    emit_1(OP_PRINT, "y");                                        \
    emit_1(OP_PRINT, "y2");                                       \
    emit_1(OP_PRINT, "z");                                        \
    emit_1(OP_PRINT, "a");                                        \
    emit_1(OP_PRINT, "msg");                                      \
    emit_1(OP_PRINT, "result_add");                               \
    emit_1(OP_PRINT, "result_sub");                               \
    emit_1(OP_PRINT, "result_mul");                               \
    emit_1(OP_PRINT, "result_div");                               \
    emit_0(OP_HALT);                                              \
  } while(0)

int main(int argc, char **argv) {
  VM _vm           = {0};
  VM *vm           = &_vm;
  Instruction **bc = NULL;
  uint8_t next_reg = 0;
  EmeraldsTable registers;
  table_init(&registers);

  emit_example_bytecode();
  vm_init(vm, bc);
  vm_execute(vm);

  table_deinit(&registers);
}
