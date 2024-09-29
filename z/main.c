#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "../libs/EmeraldsVector/export/EmeraldsVector.h"

#define OP_NIL           0x00
#define OP_FALSE         0x01
#define OP_TRUE          0x02
#define OP_INT           0x03
#define OP_FLOAT         0x04
#define OP_STRING        0x05
#define OP_ADD           0x06
#define OP_SUB           0x07
#define OP_MUL           0x08
#define OP_DIV           0x09
#define OP_JUMP          0x0A
#define OP_JUMP_IF_FALSE 0x0B
#define OP_HALT          0x0C

#define MAX_REGISTERS 256

typedef struct {
  uint8_t opcode;
  int operands[3];
  union {
    double float_val;
    char *string_val;
  } data;
} Instruction;

typedef struct {
  double registers[MAX_REGISTERS];
  size_t ip;
  Instruction **bytecode;
} VM;




Instruction *create_instruction(uint8_t opcode, int op1, int op2, int op3) {
  Instruction *i = (Instruction *)malloc(sizeof(Instruction));

  i->opcode          = opcode;
  i->operands[0]     = op1;
  i->operands[1]     = op2;
  i->operands[2]     = op3;
  i->data.float_val  = 0.0;
  i->data.string_val = NULL;

  return i;
}

#define emit(bc, i) vector_add(bc, i)

void free_bytecode(Instruction **bc) {
  for(size_t index = 0; index < vector_size(bc); index++) {
    Instruction *i = bc[index];
    if(i->opcode == OP_STRING && i->data.string_val != NULL) {
      free(i->data.string_val);
    }
    free(i);
  }
  vector_free(bc);
}

void vm_init(VM *vm, Instruction **bytecode) {
  memset(vm->registers, 0, sizeof(vm->registers));
  vm->bytecode = bytecode;
  vm->ip       = 0;
}

void vm_execute(VM *vm) {
#if defined(__GNUC__) || defined(__clang__)
  static void *_computed_gotos[] = {
    &&_computed_goto_OP_NIL,
    &&_computed_goto_OP_FALSE,
    &&_computed_goto_OP_TRUE,
    &&_computed_goto_OP_INT,
    &&_computed_goto_OP_FLOAT,
    &&_computed_goto_OP_STRING,
    &&_computed_goto_OP_ADD,
    &&_computed_goto_OP_SUB,
    &&_computed_goto_OP_MUL,
    &&_computed_goto_OP_DIV,
    &&_computed_goto_OP_JUMP,
    &&_computed_goto_OP_JUMP_IF_FALSE,
    &&_computed_goto_OP_HALT
  };
  #define switch_opcode                    \
    Instruction *i = vm->bytecode[vm->ip]; \
    goto *_computed_gotos[i->opcode];
  #define case_opcode(op) _computed_goto_##op:
  #define default_opcode \
  _err:
  #define next_opcode         \
    vm->ip++;                 \
    i = vm->bytecode[vm->ip]; \
    goto *_computed_gotos[i->opcode]
  #define skip_opcode goto *_computed_gotos[i->opcode]
#else
  #define switch_opcode       \
    Instruction *i;           \
  _opcode_loop:               \
    i = vm->bytecode[vm->ip]; \
    switch(i->opcode)
  #define case_opcode(op) case((op)):
  #define default_opcode  default:
  #define next_opcode \
    vm->ip++;         \
    goto _opcode_loop
  #define skip_opcode goto _opcode_loop
#endif

  switch_opcode {
    case_opcode(OP_NIL) {
      vm->registers[i->operands[0]] = 0.0;
      printf("NIL: R%d = nil\n", i->operands[0]);
      next_opcode;
    }
    case_opcode(OP_FALSE) {
      vm->registers[i->operands[0]] = 0.0;
      printf("FALSE: R%d = false\n", i->operands[0]);
      next_opcode;
    }
    case_opcode(OP_TRUE) {
      vm->registers[i->operands[0]] = 1.0;
      printf("TRUE: R%d = true\n", i->operands[0]);
      next_opcode;
    }
    case_opcode(OP_INT) {
      vm->registers[i->operands[0]] = (double)i->operands[1];
      printf("INT: R%d = %d\n", i->operands[0], i->operands[1]);
      next_opcode;
    }
    case_opcode(OP_FLOAT) {
      vm->registers[i->operands[0]] = i->data.float_val;
      printf("FLOAT: R%d = %g\n", i->operands[0], i->data.float_val);
      next_opcode;
    }
    case_opcode(OP_STRING) {
      vm->registers[i->operands[0]] = (double)(intptr_t)i->data.string_val;
      printf("STRING: R%d = \"%s\"\n", i->operands[0], i->data.string_val);
      next_opcode;
    }
    case_opcode(OP_ADD) {
      vm->registers[i->operands[0]] =
        vm->registers[i->operands[1]] + vm->registers[i->operands[2]];
      printf(
        "ADD: R%d = R%d(%g) + R%d(%g) = %g\n",
        i->operands[0],
        i->operands[1],
        vm->registers[i->operands[1]],
        i->operands[2],
        vm->registers[i->operands[2]],
        vm->registers[i->operands[0]]
      );
      next_opcode;
    }
    case_opcode(OP_SUB) {
      vm->registers[i->operands[0]] =
        vm->registers[i->operands[1]] - vm->registers[i->operands[2]];
      printf(
        "SUB: R%d = R%d(%g) - R%d(%g) = %g\n",
        i->operands[0],
        i->operands[1],
        vm->registers[i->operands[1]],
        i->operands[2],
        vm->registers[i->operands[2]],
        vm->registers[i->operands[0]]
      );
      next_opcode;
    }
    case_opcode(OP_MUL) {
      vm->registers[i->operands[0]] =
        vm->registers[i->operands[1]] * vm->registers[i->operands[2]];
      printf(
        "MUL: R%d = R%d(%g) * R%d(%g) = %g\n",
        i->operands[0],
        i->operands[1],
        vm->registers[i->operands[1]],
        i->operands[2],
        vm->registers[i->operands[2]],
        vm->registers[i->operands[0]]
      );
      next_opcode;
    }
    case_opcode(OP_DIV) {
      if(vm->registers[i->operands[2]] == 0.0) {
        fprintf(stderr, "Runtime Error: Division by zero\n");
        exit(1);
      }
      vm->registers[i->operands[0]] =
        vm->registers[i->operands[1]] / vm->registers[i->operands[2]];
      printf(
        "DIV: R%d = R%d(%g) / R%d(%g) = %g\n",
        i->operands[0],
        i->operands[1],
        vm->registers[i->operands[1]],
        i->operands[2],
        vm->registers[i->operands[2]],
        vm->registers[i->operands[0]]
      );
      next_opcode;
    }
    case_opcode(OP_JUMP) {
      if(i->operands[0] < 0 || i->operands[0] >= vector_size(vm->bytecode)) {
        fprintf(stderr, "Invalid jump target: %d\n", i->operands[0]);
        exit(1);
      }
      printf("JUMP: Jumping to instruction %d\n", i->operands[0]);
      vm->ip = i->operands[0];
      skip_opcode;
    }
    case_opcode(OP_JUMP_IF_FALSE) {
      int condition = (int)vm->registers[i->operands[0]];
      printf(
        "JUMP_IF_FALSE: R%d(%d) is %s, jumping to instruction %d\n",
        i->operands[0],
        condition,
        condition ? "true" : "false",
        i->operands[1]
      );
      if(!condition) {
        if(i->operands[1] < 0 || i->operands[1] >= vector_size(vm->bytecode)) {
          fprintf(stderr, "Invalid jump target: %d\n", i->operands[1]);
          exit(1);
        }
        vm->ip = i->operands[1];
        skip_opcode;
      } else {
        next_opcode;
      }
    }
    case_opcode(OP_HALT) {
      printf("HALT: Stopping VM execution.\n");
      exit(0);
    }
    default_opcode {
      fprintf(stderr, "Unknown opcode: %d\n", i->opcode);
      exit(1);
    }
  }
}

void emit_data(FILE *fp, uint8_t opcode, void *data) {
  switch(opcode) {
  case OP_FLOAT:
    if(data == NULL) {
      fprintf(stderr, "OP_FLOAT requires float data.\n");
      exit(1);
    }
    fwrite(data, sizeof(double), 1, fp);
    break;
  case OP_STRING:
    if(data == NULL) {
      fprintf(stderr, "OP_STRING requires string data.\n");
      exit(1);
    } else {
      char *str           = (char *)data;
      uint32_t str_length = strlen(str);
      fwrite(&str_length, sizeof(uint32_t), 1, fp);
      fwrite(str, 1, str_length, fp);
    }
    break;
  default:
    break;
  }
}

int get_register(EmeraldsTable *map, int *current_reg_ptr, const char *var) {
  size_t reg_ptr = table_get(map, var);
  if(reg_ptr != TABLE_UNDEFINED) {
    return reg_ptr;
  } else {
    int reg = *current_reg_ptr;
    table_add(map, var, reg);
    *current_reg_ptr = (*current_reg_ptr % MAX_REGISTERS) + 1;
    return reg;
  }
}

void write_byte(FILE *fp, uint8_t byte) { fwrite(&byte, 1, 1, fp); }
void write_word(FILE *fp, uint32_t word) {
  fwrite(&word, sizeof(uint32_t), 1, fp);
}
void write_dword(FILE *fp, double dword) {
  fwrite(&dword, sizeof(double), 1, fp);
}
void write_length(FILE *fp, const char *str, uint32_t length) {
  fwrite(str, 1, length, fp);
}

#define emit_0(opcode) (write_byte(fp, (opcode)))

#define emit_1(opcode, op1)                                     \
  do {                                                          \
    write_byte(fp, (opcode));                                   \
    write_byte(fp, get_register(&registers, &next_reg, (op1))); \
  } while(0)

#define emit_int(opcode, op1, op2)                              \
  do {                                                          \
    write_byte(fp, (opcode));                                   \
    write_byte(fp, get_register(&registers, &next_reg, (op1))); \
    write_word(fp, (op2));                                      \
  } while(0)

#define emit_float(opcode, op1, op2)                            \
  do {                                                          \
    write_byte(fp, (opcode));                                   \
    write_byte(fp, get_register(&registers, &next_reg, (op1))); \
    write_dword(fp, (op2));                                     \
  } while(0)

#define emit_string(opcode, op1, op2)                           \
  do {                                                          \
    write_byte(fp, (opcode));                                   \
    write_byte(fp, get_register(&registers, &next_reg, (op1))); \
                                                                \
    /* TODO - Care for this */                                  \
    uint32_t str_length = strlen((op2));                        \
    fwrite(&str_length, sizeof(uint32_t), 1, fp);               \
    write_length(fp, (op2), str_length);                        \
  } while(0)

#define emit_3(opcode, op1, op2, op3)                           \
  do {                                                          \
    write_byte(fp, (opcode));                                   \
    write_byte(fp, get_register(&registers, &next_reg, (op1))); \
    write_byte(fp, get_register(&registers, &next_reg, (op2))); \
    write_byte(fp, get_register(&registers, &next_reg, (op3))); \
  } while(0)

Instruction *load_instruction(FILE *fp) {
  uint8_t opcode;
  size_t read    = fread(&opcode, 1, 1, fp);
  Instruction *i = create_instruction(opcode, 0, 0, 0);

  switch(opcode) {
  case OP_NIL:
  case OP_FALSE:
  case OP_TRUE:
  case OP_HALT: {
    uint8_t reg;
    fread(&reg, 1, 1, fp);
    i->operands[0] = reg;
    break;
  }
  case OP_INT: {
    uint8_t reg;
    int32_t int_val;
    fread(&reg, 1, 1, fp);
    fread(&int_val, sizeof(int32_t), 1, fp);
    i->operands[0] = reg;
    i->operands[1] = int_val;
    break;
  }
  case OP_FLOAT: {
    uint8_t reg;
    double float_val;
    fread(&reg, 1, 1, fp);
    fread(&float_val, sizeof(double), 1, fp);
    i->operands[0]    = reg;
    i->data.float_val = float_val;
    break;
  }
  case OP_STRING: {
    uint8_t reg;
    uint32_t str_length;
    fread(&reg, 1, 1, fp);
    fread(&str_length, sizeof(uint32_t), 1, fp);
    char *str = (char *)malloc(str_length + 1);
    fread(str, 1, str_length, fp);
    str[str_length]    = '\0';
    i->operands[0]     = reg;
    i->data.string_val = str;
    break;
  }
  case OP_ADD:
  case OP_SUB:
  case OP_MUL:
  case OP_DIV: {
    uint8_t dest, src1, src2;
    fread(&dest, 1, 1, fp);
    fread(&src1, 1, 1, fp);
    fread(&src2, 1, 1, fp);
    i->operands[0] = dest;
    i->operands[1] = src1;
    i->operands[2] = src2;
    break;
  }
  case OP_JUMP: {
    uint32_t target_idx;
    fread(&target_idx, sizeof(uint32_t), 1, fp);
    i->operands[0] = target_idx;
    break;
  }
  case OP_JUMP_IF_FALSE: {
    uint8_t reg;
    uint32_t target_idx;
    fread(&reg, 1, 1, fp);
    fread(&target_idx, sizeof(uint32_t), 1, fp);
    i->operands[0] = reg;
    i->operands[1] = target_idx;
    break;
  }
  default:
    fprintf(stderr, "Unknown opcode in bytecode: %d\n", opcode);
    exit(1);
  }

  return i;
}

void load_bytecode(const char *filename, Instruction ***bc) {
  char magic[4];
  uint8_t version;

  FILE *fp = fopen(filename, "rb");

  *bc = NULL;

  fread(magic, 1, 4, fp);
  fread(&version, 1, 1, fp);

  while(true) {
    Instruction *i = load_instruction(fp);
    if(!i) {
      break;
    } else if(i->opcode == OP_HALT) {
      emit(*bc, i);
      break;
    } else {
      emit(*bc, i);
    }
  }

  fclose(fp);
}

void create_example_bytecode(const char *filename) {
  FILE *fp = fopen(filename, "wb");

  EmeraldsTable registers;
  table_init(&registers);
  int next_reg = 0;

  fwrite("MARG", 1, 4, fp);
  uint8_t version = 1;
  fwrite(&version, 1, 1, fp);

  emit_1(OP_NIL, "x");
  emit_1(OP_TRUE, "y");
  emit_int(OP_INT, "z", 10);
  emit_float(OP_FLOAT, "a", 3.14);
  emit_string(OP_STRING, "msg", "Hello");
  emit_3(OP_ADD, "result_add", "z", "a");
  emit_3(OP_SUB, "result_sub", "result_add", "y");
  emit_3(OP_MUL, "result_mul", "result_sub", "z");
  emit_3(OP_DIV, "result_div", "result_mul", "a");
  emit_0(OP_HALT);

  table_deinit(&registers);
  fclose(fp);
}

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage: %s <bytecode_file> [--create]\n", argv[0]);
    printf("Example: %s program.bytecode\n", argv[0]);
    printf("To create an example bytecode file: %s --create\n", argv[0]);
    return 1;
  } else if(strcmp(argv[1], "--create") == 0) {
    const char *example_filename = "example.bytecode";
    create_example_bytecode(example_filename);
    printf("Created example bytecode file: %s\n", example_filename);
    return 0;
  } else {
    Instruction **bc = NULL;
    VM vm            = {0};

    load_bytecode(argv[1], &bc);

    vm_init(&vm, bc);
    vm_execute(&vm);
    free_bytecode(bc);

    return 0;
  }
}
