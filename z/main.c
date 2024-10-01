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

#define O(op) vector_add(bc, ((op) << 24))
#define OAk(op, a, k)                               \
  vector_add(                                       \
    bc,                                             \
    (((op) << 24) | (get_register(vm, (a)) << 16) | \
     (make_constant(vm, (k)) & 0x0000ffff))         \
  )
#define OABk(op, a, bk)                             \
  vector_add(                                       \
    bc,                                             \
    (((op) << 24) | (get_register(vm, (a)) << 16) | \
     (make_constant(vm, (bk)) & 0x0000ffff))        \
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

typedef struct {
  Value registers[MAX_REGISTERS];
  Value constants[MAX_CONSTANTS];
  uint8_t num_constants;
  size_t ip;
  uint32_t *bytecode;
  uint8_t current_reg_index;
  EmeraldsTable local_variables;
} VM;

typedef struct Object {
  bool is_marked;
  Type type;
  struct Object *next;
  VM *bound_vm;
} Object;

Object *value_object_new(VM *bound_vm, size_t size, Type type) {
  Object *self = (Object *)malloc(sizeof(Object) * size);

  self->is_marked = false;
  self->type      = type;
  self->next      = NULL;
  self->bound_vm  = bound_vm;

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

void vm_init(VM *vm) {
  vm->num_constants     = 0;
  vm->ip                = 0;
  vm->bytecode          = NULL;
  vm->current_reg_index = 0;
  table_init(&vm->local_variables);
}

uint8_t make_constant(VM *vm, Value value) {
  vm->constants[vm->num_constants++] = value;
  return vm->num_constants - 1;
}

void vm_execute(VM *vm) {
#if defined(__GNUC__) || defined(__clang__)
  static void *_computed_gotos[256] = {
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
    &&_computed_goto_OP_HALT,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR,
    &&_computed_goto_ERROR
  };
  #define switch_opcode       \
    uint32_t i;               \
  _opcode_loop:               \
    i = vm->bytecode[vm->ip]; \
    goto *_computed_gotos[FETCH(i)];
  #define case_opcode(op) _computed_goto_##op:
  #define default_opcode \
  _computed_goto_ERROR:
#else
  #define switch_opcode       \
    uint32_t i;               \
  _opcode_loop:               \
    i = vm->bytecode[vm->ip]; \
    switch(FETCH(i))
  #define case_opcode(op) case(op):
  #define default_opcode  default:
#endif

#define next_opcode \
  vm->ip++;         \
  goto _opcode_loop
#define skip_opcode goto _opcode_loop

  switch_opcode {
    case_opcode(OP_NIL) {
      vm->registers[A(i)] = NIL();
      next_opcode;
    }
    case_opcode(OP_FALSE) {
      vm->registers[A(i)] = FALSE();
      next_opcode;
    }
    case_opcode(OP_TRUE) {
      vm->registers[A(i)] = TRUE();
      next_opcode;
    }
    case_opcode(OP_NUMBER) {
      vm->registers[A(i)] = vm->constants[Bk(i)];
      next_opcode;
    }
    case_opcode(OP_STRING) {
      vm->registers[A(i)] = vm->constants[Bk(i)];
      next_opcode;
    }
    case_opcode(OP_ADD) {
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value +
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_SUB) {
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value -
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_MUL) {
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value *
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_DIV) {
      if(AS_NUMBER(vm->registers[C(i)])->value == 0.0) {
        fprintf(stderr, "Runtime Error: Division by zero\n");
        exit(1);
      }
      vm->registers[A(i)] = NUMBER(
        AS_NUMBER(vm->registers[B(i)])->value /
        AS_NUMBER(vm->registers[C(i)])->value
      );
      next_opcode;
    }
    case_opcode(OP_JUMP) {
      if(Bk(i) >= MAX_CONSTANTS) {
        fprintf(stderr, "Invalid jump target: %u\n", Bk(i));
        exit(1);
      }
      vm->ip = Bk(i);
      skip_opcode;
    }
    case_opcode(OP_JUMP_IF_FALSE) {
      Value condition = vm->registers[A(i)];
      bool is_false   = IS_FALSE(condition) || IS_NIL(condition);
      if(is_false) {
        if(Bk(i) >= MAX_CONSTANTS) {
          fprintf(stderr, "Invalid jump target: %u\n", Bk(i));
          exit(1);
        }
        vm->ip = Bk(i);
        skip_opcode;
      } else {
        next_opcode;
      }
    }
    case_opcode(OP_PRINT) {
      Value v = vm->registers[A(i)];
      if(IS_NIL(v)) {
        printf("R%d = nil\n", A(i));
      } else if(IS_FALSE(v)) {
        printf("R%d = false\n", A(i));
      } else if(IS_TRUE(v)) {
        printf("R%d = true\n", A(i));
      } else if(IS_NUMBER(v)) {
        printf("R%d = %g\n", A(i), AS_NUMBER(v)->value);
      } else if(IS_STRING(v)) {
        printf("R%d = \"%s\"\n", A(i), AS_STRING(v)->value);
      } else {
        printf("R%d = UNKNOWN\n", A(i));
      }
      next_opcode;
    }
    case_opcode(OP_HALT) {
      printf("HALT: Stopping VM execution.\n");
      exit(0);
    }
    default_opcode {
      fprintf(stderr, "Unknown opcode: %d\n", FETCH(i));
      exit(1);
    }
  }
}

uint8_t get_register(VM *vm, const char *var) {
  size_t reg_ptr = table_get(&vm->local_variables, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    uint8_t reg = vm->current_reg_index;
    table_add(&vm->local_variables, var, reg);
    vm->current_reg_index = (vm->current_reg_index % MAX_REGISTERS) + 1;
    return reg;
  }
}

uint32_t *emit_example_bytecode(VM *vm) {
  uint32_t *bc = NULL;

  OAk(OP_NIL, "x", NIL());
  OAk(OP_FALSE, "y", FALSE());
  OAk(OP_TRUE, "y2", TRUE());
  OAk(OP_NUMBER, "y3", NUMBER(1));
  OAk(OP_NUMBER, "z", NUMBER(10));
  OAk(OP_NUMBER, "a", NUMBER(3.14));
  OAk(OP_STRING, "msg", STRING("Hello"));
  OABC(OP_ADD, "result_add", "z", "a");
  OABC(OP_SUB, "result_sub", "result_add", "y3");
  OABC(OP_MUL, "result_mul", "result_sub", "z");
  OABC(OP_DIV, "result_div", "result_mul", "a");
  OA(OP_PRINT, "x");
  OA(OP_PRINT, "y");
  OA(OP_PRINT, "y2");
  OA(OP_PRINT, "y3");
  OA(OP_PRINT, "z");
  OA(OP_PRINT, "a");
  OA(OP_PRINT, "msg");
  OA(OP_PRINT, "result_add");
  OA(OP_PRINT, "result_sub");
  OA(OP_PRINT, "result_mul");
  OA(OP_PRINT, "result_div");
  O(OP_HALT);

  return bc;
}

int main(void) {
  VM _vm = {0};
  VM *vm = &_vm;

  vm_init(vm);
  vm->bytecode = emit_example_bytecode(vm);
  vm_execute(vm);
}
