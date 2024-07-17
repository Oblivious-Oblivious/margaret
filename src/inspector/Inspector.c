#include "Inspector.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../opcode/MargValue.h"
#include "../opcode/opcodes.h"

#include <stdio.h> /* printf */

static void write_offset_and_line_number_on(
  char **disassembled_instruction, size_t offset
) {
  string_addf(*disassembled_instruction, "%04zx    ", offset);
  string_add(*disassembled_instruction, "     |      ");
}

/**
 * @brief Disassembles a simple instruction
 * @param res -> Adds log information to the res vector
 * @param name -> Name of opcode
 * @param proc -> Current proc from which we display bytecode
 * @param offset -> Current offset
 * @return size_t -> Newly calculated offset
 */
static size_t
instruction_single(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode = proc->bytecode[offset];

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(disassembled_instruction, "%02x                  ", opcode);
  string_addf(disassembled_instruction, "%s", name);
  vector_add(*res, disassembled_instruction);

  return offset + 1;
}

static size_t
instruction_send(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode             = proc->bytecode[offset];
  uint8_t message_name_index = proc->bytecode[offset + 1];

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x               ",
    opcode,
    message_name_index
  );
  string_addf(disassembled_instruction, "%-24s #", name);
  string_add(
    disassembled_instruction,
    marg_value_as_variable(proc->temporaries[message_name_index])
  );
  vector_add(*res, disassembled_instruction);

  return offset + 2;
}

static size_t
instruction_send_word(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[2] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
  };
  uint16_t message_name_index = bytes_to_word(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x            ",
    opcode,
    bytes[0],
    bytes[1]
  );
  string_addf(disassembled_instruction, "%-24s #", name);
  string_add(
    disassembled_instruction,
    marg_value_as_variable(proc->temporaries[message_name_index])
  );
  vector_add(*res, disassembled_instruction);

  return offset + 3;
}

static size_t
instruction_send_dword(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[4] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
    proc->bytecode[offset + 3],
    proc->bytecode[offset + 4],
  };
  uint32_t message_name_index = bytes_to_dword(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x %02x %02x      ",
    opcode,
    bytes[0],
    bytes[1],
    bytes[2],
    bytes[3]
  );
  string_addf(disassembled_instruction, "%-24s #", name);
  string_add(
    disassembled_instruction,
    marg_value_as_variable(proc->temporaries[message_name_index])
  );
  vector_add(*res, disassembled_instruction);

  return offset + 5;
}

static size_t
instruction_object(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode    = proc->bytecode[offset];
  uint8_t temporary = proc->bytecode[offset + 1];

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction, "%02x %02x               ", opcode, temporary
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction, marg_value_format(proc->temporaries[temporary])
  );
  string_addf(disassembled_instruction, " @[%d]", temporary);
  vector_add(*res, disassembled_instruction);

  return offset + 2;
}

static size_t instruction_object_word(
  char ***res, char *name, MargProc *proc, size_t offset
) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[2] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
  };
  uint16_t temporary = bytes_to_word(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x            ",
    opcode,
    bytes[0],
    bytes[1]
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction, marg_value_format(proc->temporaries[temporary])
  );
  string_addf(disassembled_instruction, " @[%d]", temporary);
  vector_add(*res, disassembled_instruction);

  return offset + 3;
}

static size_t instruction_object_dword(
  char ***res, char *name, MargProc *proc, size_t offset
) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[4] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
    proc->bytecode[offset + 3],
    proc->bytecode[offset + 4],
  };
  uint32_t temporary = bytes_to_dword(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x %02x %02x      ",
    opcode,
    bytes[0],
    bytes[1],
    bytes[2],
    bytes[3]
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction, marg_value_format(proc->temporaries[temporary])
  );
  string_addf(disassembled_instruction, " @[%d]", temporary);
  vector_add(*res, disassembled_instruction);

  return offset + 5;
}

static size_t
instruction_variable(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t variable = proc->bytecode[offset + 1];

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction, "%02x %02x               ", opcode, variable
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction,
    marg_value_as_variable(proc->temporaries[variable])
  );
  string_addf(disassembled_instruction, " @[%d]", variable);
  vector_add(*res, disassembled_instruction);

  return offset + 2;
}

static size_t instruction_variable_word(
  char ***res, char *name, MargProc *proc, size_t offset
) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[2] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
  };
  uint16_t variable = bytes_to_word(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x            ",
    opcode,
    proc->bytecode[offset + 1],
    bytes[1]
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction,
    marg_value_as_variable(proc->temporaries[variable])
  );
  string_addf(disassembled_instruction, " @[%d]", variable);
  vector_add(*res, disassembled_instruction);

  return offset + 3;
}

static size_t instruction_variable_dword(
  char ***res, char *name, MargProc *proc, size_t offset
) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[4] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
    proc->bytecode[offset + 3],
    proc->bytecode[offset + 4],
  };
  uint32_t variable = bytes_to_dword(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x %02x %02x      ",
    opcode,
    proc->bytecode[offset + 1],
    bytes[1],
    bytes[2],
    bytes[3]
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction,
    marg_value_as_variable(proc->temporaries[variable])
  );
  string_addf(disassembled_instruction, " @[%d]", variable);
  vector_add(*res, disassembled_instruction);

  return offset + 5;
}

static size_t
instruction_array_type(char ***res, char *name, MargProc *proc, size_t offset) {
  uint8_t opcode             = proc->bytecode[offset];
  uint8_t number_of_elements = proc->bytecode[offset + 1];

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x               ",
    opcode,
    number_of_elements
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction,
    marg_value_format(proc->temporaries[number_of_elements])
  );
  vector_add(*res, disassembled_instruction);

  return offset + 2;
}

static size_t instruction_array_type_word(
  char ***res, char *name, MargProc *proc, size_t offset
) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[2] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
  };
  uint16_t number_of_elements = bytes_to_word(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x            ",
    opcode,
    proc->bytecode[offset + 1],
    bytes[1]
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction,
    marg_value_format(proc->temporaries[number_of_elements])
  );
  vector_add(*res, disassembled_instruction);

  return offset + 3;
}

static size_t instruction_array_type_dword(
  char ***res, char *name, MargProc *proc, size_t offset
) {
  uint8_t opcode   = proc->bytecode[offset];
  uint8_t bytes[4] = {
    proc->bytecode[offset + 1],
    proc->bytecode[offset + 2],
    proc->bytecode[offset + 3],
    proc->bytecode[offset + 4],
  };
  uint32_t number_of_elements = bytes_to_dword(bytes);

  char *disassembled_instruction = string_new("");
  write_offset_and_line_number_on(&disassembled_instruction, offset);
  string_addf(
    disassembled_instruction,
    "%02x %02x %02x %02x %02x      ",
    opcode,
    proc->bytecode[offset + 1],
    bytes[1],
    bytes[2],
    bytes[3]
  );
  string_addf(disassembled_instruction, "%-24s ", name);
  string_add(
    disassembled_instruction,
    marg_value_format(proc->temporaries[number_of_elements])
  );
  vector_add(*res, disassembled_instruction);

  return offset + 5;
}

/**
 * @brief Inspects an instruction inside of a proc
 * @param res -> Adds log information to the res vector
 * @param proc -> The proc from which bytecodes are to be inspected
 * @param offset -> The current offset of the bytecode in the array
 * @return size_t -> The newly calculated offset
 */
static size_t inspect_instruction(char ***res, MargProc *proc, size_t offset) {
  uint8_t instruction = proc->bytecode[offset];
  switch(instruction) {
  case OP_HALT:
    return instruction_single(res, "HALT", proc, offset);
  case OP_POP:
    return instruction_single(res, "POP", proc, offset);

  case OP_PUT_NIL:
    return instruction_single(res, "PUT_NIL", proc, offset);
  case OP_PUT_TRUE:
    return instruction_single(res, "PUT_TRUE", proc, offset);
  case OP_PUT_FALSE:
    return instruction_single(res, "PUT_FALSE", proc, offset);

  case OP_PUT_SELF:
    return instruction_single(res, "PUT_SELF", proc, offset);
  case OP_PUT_SUPER:
    return instruction_single(res, "PUT_SUPER", proc, offset);

  case OP_PUT_MINUS_1:
    return instruction_single(res, "PUT_MINUS_1", proc, offset);
  case OP_PUT_0:
    return instruction_single(res, "PUT_0", proc, offset);
  case OP_PUT_1:
    return instruction_single(res, "PUT_1", proc, offset);
  case OP_PUT_2:
    return instruction_single(res, "PUT_2", proc, offset);

  case OP_PUT_OBJECT:
    return instruction_object(res, "PUT_OBJECT", proc, offset);
  case OP_PUT_OBJECT_WORD:
    return instruction_object_word(res, "PUT_OBJECT_WORD", proc, offset);
  case OP_PUT_OBJECT_DWORD:
    return instruction_object_dword(res, "PUT_OBJECT_DWORD", proc, offset);

  case OP_PUT_TENSOR:
    return instruction_array_type(res, "PUT_TENSOR", proc, offset);
  case OP_PUT_TENSOR_WORD:
    return instruction_array_type_word(res, "PUT_TENSOR_WORD", proc, offset);
  case OP_PUT_TENSOR_DWORD:
    return instruction_array_type_dword(res, "PUT_TENSOR_DWORD", proc, offset);
  // case OP_PUT_TUPLE:
  //     return instruction_array_type(res, "PUT_TUPLE", proc, offset);
  // case OP_PUT_TUPLE_WORD:
  //     return instruction_array_type_word(res, "PUT_TUPLE_WORD", proc,
  //     offset);
  // case OP_PUT_TUPLE_DWORD:
  //     return instruction_array_type_dword(res, "PUT_TUPLE_DWORD", proc,
  //     offset);
  case OP_PUT_HASH:
    return instruction_array_type(res, "PUT_HASH", proc, offset);
  case OP_PUT_HASH_WORD:
    return instruction_array_type_word(res, "PUT_HASH_WORD", proc, offset);
  case OP_PUT_HASH_DWORD:
    return instruction_array_type_dword(res, "PUT_HASH_DWORD", proc, offset);
    // case OP_PUT_BITSTRING:
    //     return instruction_array_type(res, "PUT_BITSTRING", proc, offset);
    // case OP_PUT_BITSTRING_WORD:
    //     return instruction_array_type_word(res, "PUT_BITSTRING_WORD", proc,
    //     offset);
    // case OP_PUT_BITSTRING_DWORD:
    //     return instruction_array_type_dword(res, "PUT_BITSTRING_DWORD",
    //     proc, offset);

    // case OP_PUT_LABEL:
    //     return offset + ??;
    // case OP_GOTO:
    //     return offset + ??;
    // case OP_GOTO_LOCAL:
    //     return offset + ??;

  case OP_SET_GLOBAL:
    return instruction_variable(res, "SET_GLOBAL", proc, offset);
  case OP_SET_GLOBAL_WORD:
    return instruction_variable_word(res, "SET_GLOBAL_WORD", proc, offset);
  case OP_SET_GLOBAL_DWORD:
    return instruction_variable_dword(res, "SET_GLOBAL_DWORD", proc, offset);
  case OP_SET_INSTANCE:
    return instruction_variable(res, "SET_INSTANCE", proc, offset);
  case OP_SET_INSTANCE_WORD:
    return instruction_variable_word(res, "SET_INSTANCE_WORD", proc, offset);
  case OP_SET_INSTANCE_DWORD:
    return instruction_variable_dword(res, "SET_INSTANCE_DWORD", proc, offset);
  case OP_SET_LOCAL:
    return instruction_variable(res, "SET_LOCAL", proc, offset);
  case OP_SET_LOCAL_WORD:
    return instruction_variable_word(res, "SET_LOCAL_WORD", proc, offset);
  case OP_SET_LOCAL_DWORD:
    return instruction_variable_dword(res, "SET_LOCAL_DWORD", proc, offset);

  case OP_GET_GLOBAL:
    return instruction_variable(res, "GET_GLOBAL", proc, offset);
  case OP_GET_GLOBAL_WORD:
    return instruction_variable_word(res, "GET_GLOBAL_WORD", proc, offset);
  case OP_GET_GLOBAL_DWORD:
    return instruction_variable_dword(res, "GET_GLOBAL_DWORD", proc, offset);
  case OP_GET_INSTANCE:
    return instruction_variable(res, "GET_INSTANCE", proc, offset);
  case OP_GET_INSTANCE_WORD:
    return instruction_variable_word(res, "GET_INSTANCE_WORD", proc, offset);
  case OP_GET_INSTANCE_DWORD:
    return instruction_variable_dword(res, "GET_INSTANCE_DWORD", proc, offset);
  case OP_GET_LOCAL:
    return instruction_variable(res, "GET_LOCAL", proc, offset);
  case OP_GET_LOCAL_WORD:
    return instruction_variable_word(res, "GET_LOCAL_WORD", proc, offset);
  case OP_GET_LOCAL_DWORD:
    return instruction_variable_dword(res, "GET_LOCAL_DWORD", proc, offset);

  case OP_SEND:
    return instruction_send(res, "SEND", proc, offset);
  case OP_SEND_WORD:
    return instruction_send_word(res, "SEND_WORD", proc, offset);
  case OP_SEND_DWORD:
    return instruction_send_dword(res, "SEND_DWORD", proc, offset);
  case OP_EXIT_ACTIVATION_RECORD:
    return instruction_single(res, "EXIT_ACTIVATION_RECORD", proc, offset);

  case OP_PUTS:
    return instruction_single(res, "PUTS", proc, offset);
  case OP_INCLUDE:
    return instruction_single(res, "INCLUDE", proc, offset);
  case OP_PROC_CALL:
    return instruction_single(res, "PROC_CALL", proc, offset);
  case OP_PROC_CALL_PARAMS:
    return instruction_single(res, "PROC_CALL_PARAMS", proc, offset);

  case OP_PRIM_MESSAGES:
    return instruction_single(res, "PRIM_MESSAGES", proc, offset);
  case OP_PRIM_OBJECT_ID:
    return instruction_single(res, "PRIM_OBJECT_ID", proc, offset);
  case OP_PRIM_TO_STRING:
    return instruction_single(res, "PRIM_TO_STRING", proc, offset);
  case OP_PRIM_EQUALS:
    return instruction_single(res, "PRIM_EQUALS", proc, offset);
  case OP_PRIM_EQUALS_NUMERIC:
    return instruction_single(res, "PRIM_EQUALS_NUMERIC", proc, offset);
  case OP_PRIM_DNU:
    return instruction_single(res, "PRIM_DNU", proc, offset);
  case OP_PRIM_CLONE_OBJECT:
    return instruction_single(res, "PRIM_CLONE_OBJECT", proc, offset);
  case OP_PRIM_BIND_METHOD:
    return instruction_single(res, "PRIM_BIND_METHOD", proc, offset);
  case OP_PRIM_ADD:
    return instruction_single(res, "PRIM_ADD", proc, offset);
  case OP_PRIM_SUB:
    return instruction_single(res, "PRIM_SUB", proc, offset);
  case OP_PRIM_MUL:
    return instruction_single(res, "PRIM_MUL", proc, offset);
  case OP_PRIM_DIV:
    return instruction_single(res, "PRIM_DIV", proc, offset);
  case OP_PRIM_ABS:
    return instruction_single(res, "PRIM_ABS", proc, offset);
  case OP_PRIM_LT:
    return instruction_single(res, "PRIM_LT", proc, offset);
  case OP_PRIM_GT:
    return instruction_single(res, "PRIM_GT", proc, offset);
  case OP_PRIM_LTE:
    return instruction_single(res, "PRIM_LTE", proc, offset);
  case OP_PRIM_GTE:
    return instruction_single(res, "PRIM_GTE", proc, offset);
  case OP_PRIM_INCR:
    return instruction_single(res, "PRIM_INCR", proc, offset);
  case OP_PRIM_DECR:
    return instruction_single(res, "PRIM_DECR", proc, offset);
  case OP_PRIM_DOUBLE:
    return instruction_single(res, "PRIM_DOUBLE", proc, offset);

  default: {
    char *unknown_opcode = string_new("");
    string_addf(unknown_opcode, "Unknown opcode %d", instruction);
    vector_add(*res, unknown_opcode);
    return offset + 1;
  }
  }
}

char **inspect_vm_bytecode(VM *vm) {
  char **res = NULL;

  size_t number_of_bytecodes = vector_size(vm->current->bytecode);
  for(size_t offset = 0; offset < number_of_bytecodes;) {
    offset = inspect_instruction(&res, vm->current, offset);
  }

  return res;
}

void inspect_and_print_vm_bytecode(VM *vm) {
  char **disassembled = inspect_vm_bytecode(vm);

  size_t disassembled_size = vector_size(disassembled);
  for(size_t i = 0; i < disassembled_size; i++) {
    printf("%s\n", disassembled[i]);
  }
}

void inspect_and_print_proc(VM *vm) {
  printf("\n/-------------- Disassembly: <proc> ------------\\\n");
  inspect_and_print_vm_bytecode(vm);
  printf("\\-----------------------------------------------/\n\n");
}

void inspect_and_print_method(VM *vm) {
  printf(
    "\n/--------------- Disassembly: < #%s > ---------\\\n",
    vm->current->bound_method->message_name->chars
  );
  inspect_and_print_vm_bytecode(vm);
  printf("\\-----------------------------------------------/\n\n");
}

void inspect_and_print_main(VM *vm) {
  printf("\n/-------------- Disassembly: <main> ------------\\\n");
  inspect_and_print_vm_bytecode(vm);
  printf("\\-----------------------------------------------/\n\n");
}
