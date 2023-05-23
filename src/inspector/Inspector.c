#include "Inspector.h"

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "../base/string.h"
#include "../base/chunk.h"

#include "../opcode/opcodes.h"
#include "../opcode/MargString.h"
#include "../opcode/MargProc.h"
#include "../vm/byte_conversions.h"

static void write_offset_and_line_number_on(string *disassembled_instruction, chunk *chunk, size_t offset) {
    string_addf(disassembled_instruction, "%04zx    ", offset);
    if(offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        string_add_str(disassembled_instruction, "     |      ");
    else
        string_addf(disassembled_instruction, "%6zu      ", chunk->lines[offset]);
}

/**
 * @brief Disassembles a simple instruction
 * @param res -> Adds log information to the res vector
 * @param name -> Name of opcode
 * @param chunk -> Current chunk
 * @param offset -> Current offset
 * @return size_t -> Newly calculated offset
 */
static size_t instruction_single(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x                  ", opcode);
    string_addf(disassembled_instruction, "%s", name);
    vector_add(res, disassembled_instruction);

    return offset + 1;
}

static size_t instruction_send(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t message_name_index = chunk_get(chunk, offset + 1);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x               ", opcode, message_name_index);
    string_addf(disassembled_instruction, "%-24s #", name);
    string_add(disassembled_instruction, marg_value_as_variable(chunk_temporaries_get(chunk, message_name_index)));
    vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_send_word(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[2] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
    };
    uint16_t message_name_index = bytes_to_word(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x            ", opcode, bytes[0], bytes[1]);
    string_addf(disassembled_instruction, "%-24s #", name);
    string_add(disassembled_instruction, marg_value_as_variable(chunk_temporaries_get(chunk, message_name_index)));
    vector_add(res, disassembled_instruction);

    return offset + 3;
}

static size_t instruction_send_dword(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[4] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
        chunk_get(chunk, offset + 3),
        chunk_get(chunk, offset + 4),
    };
    uint32_t message_name_index = bytes_to_dword(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, bytes[0], bytes[1], bytes[2], bytes[3]);
    string_addf(disassembled_instruction, "%-24s #", name);
    string_add(disassembled_instruction, marg_value_as_variable(chunk_temporaries_get(chunk, message_name_index)));
    vector_add(res, disassembled_instruction);

    return offset + 5;
}

static size_t instruction_object(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t temporary = chunk_get(chunk, offset + 1);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x               ", opcode, temporary);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_format(chunk_temporaries_get(chunk, temporary)));
    string_addf(disassembled_instruction, " @[%d]", temporary);
    vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_object_word(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[2] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
    };
    uint16_t temporary = bytes_to_word(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x            ", opcode, bytes[0], bytes[1]);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_format(chunk_temporaries_get(chunk, temporary)));
    string_addf(disassembled_instruction, " @[%d]", temporary);
    vector_add(res, disassembled_instruction);

    return offset + 3;
}

static size_t instruction_object_dword(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[4] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
        chunk_get(chunk, offset + 3),
        chunk_get(chunk, offset + 4),
    };
    uint32_t temporary = bytes_to_dword(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, bytes[0], bytes[1], bytes[2], bytes[3]);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_format(chunk_temporaries_get(chunk, temporary)));
    string_addf(disassembled_instruction, " @[%d]", temporary);
    vector_add(res, disassembled_instruction);

    return offset + 5;
}

static size_t instruction_variable(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t variable = chunk_get(chunk, offset + 1);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x               ", opcode, variable);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_as_variable(chunk_temporaries_get(chunk, variable)));
    string_addf(disassembled_instruction, " @[%d]", variable);
    vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_variable_word(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[2] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
    };
    uint16_t variable = bytes_to_word(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x            ", opcode, chunk_get(chunk, offset + 1), bytes[1]);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_as_variable(chunk_temporaries_get(chunk, variable)));
    string_addf(disassembled_instruction, " @[%d]", variable);
    vector_add(res, disassembled_instruction);

    return offset + 3;
}

static size_t instruction_variable_dword(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[4] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
        chunk_get(chunk, offset + 3),
        chunk_get(chunk, offset + 4),
    };
    uint32_t variable = bytes_to_dword(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, chunk_get(chunk, offset + 1), bytes[1], bytes[2], bytes[3]);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_as_variable(chunk_temporaries_get(chunk, variable)));
    string_addf(disassembled_instruction, " @[%d]", variable);
    vector_add(res, disassembled_instruction);

    return offset + 5;
}

static size_t instruction_array_type(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t number_of_elements = chunk_get(chunk, offset + 1);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x               ", opcode, number_of_elements);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_format(chunk_temporaries_get(chunk, number_of_elements)));
    vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_array_type_word(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[2] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
    };
    uint16_t number_of_elements = bytes_to_word(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x            ", opcode, chunk_get(chunk, offset + 1), bytes[1]);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_format(chunk_temporaries_get(chunk, number_of_elements)));
    vector_add(res, disassembled_instruction);

    return offset + 3;
}

static size_t instruction_array_type_dword(vector *res, char *name, chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[4] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
        chunk_get(chunk, offset + 3),
        chunk_get(chunk, offset + 4),
    };
    uint32_t number_of_elements = bytes_to_dword(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, chunk_get(chunk, offset + 1), bytes[1], bytes[2], bytes[3]);
    string_addf(disassembled_instruction, "%-24s ", name);
    string_add(disassembled_instruction, marg_value_format(chunk_temporaries_get(chunk, number_of_elements)));
    vector_add(res, disassembled_instruction);

    return offset + 5;
}

/**
 * @brief Inspects an instruction inside of a chunk
 * @param res -> Adds log information to the res vector
 * @param chunk -> The chunk from which bytecodes are to be inspected
 * @param offset -> The current offset of the bytecode in the array
 * @return size_t -> The newly calculated offset
 */
static size_t inspect_instruction(vector *res, chunk *chunk, size_t offset) {
    uint8_t instruction = chunk_get(chunk, offset);
    switch(instruction) {
        case OP_HALT:
            return instruction_single(res, "HALT", chunk, offset);
        case OP_POP:
            return instruction_single(res, "POP", chunk, offset);

        case OP_PUT_NIL:
            return instruction_single(res, "PUT_NIL", chunk, offset);
        case OP_PUT_TRUE:
            return instruction_single(res, "PUT_TRUE", chunk, offset);
        case OP_PUT_FALSE:
            return instruction_single(res, "PUT_FALSE", chunk, offset);

        case OP_PUT_SELF:
            return instruction_single(res, "PUT_SELF", chunk, offset);
        case OP_PUT_SUPER:
            return instruction_single(res, "PUT_SUPER", chunk, offset);

        case OP_PUT_MINUS_1:
            return instruction_single(res, "PUT_MINUS_1", chunk, offset);
        case OP_PUT_0:
            return instruction_single(res, "PUT_0", chunk, offset);
        case OP_PUT_1:
            return instruction_single(res, "PUT_1", chunk, offset);
        case OP_PUT_2:
            return instruction_single(res, "PUT_2", chunk, offset);

        case OP_PUT_OBJECT:
            return instruction_object(res, "PUT_OBJECT", chunk, offset);
        case OP_PUT_OBJECT_WORD:
            return instruction_object_word(res, "PUT_OBJECT_WORD", chunk, offset);
        case OP_PUT_OBJECT_DWORD:
            return instruction_object_dword(res, "PUT_OBJECT_DWORD", chunk, offset);

        case OP_PUT_TENSOR:
            return instruction_array_type(res, "PUT_TENSOR", chunk, offset);
        case OP_PUT_TENSOR_WORD:
            return instruction_array_type_word(res, "PUT_TENSOR_WORD", chunk, offset);
        case OP_PUT_TENSOR_DWORD:
            return instruction_array_type_dword(res, "PUT_TENSOR_DWORD", chunk, offset);
        // case OP_PUT_TUPLE:
        //     return instruction_array_type(res, "PUT_TUPLE", chunk, offset);
        // case OP_PUT_TUPLE_WORD:
        //     return instruction_array_type_word(res, "PUT_TUPLE_WORD", chunk, offset);
        // case OP_PUT_TUPLE_DWORD:
        //     return instruction_array_type_dword(res, "PUT_TUPLE_DWORD", chunk, offset);
        case OP_PUT_HASH:
            return instruction_array_type(res, "PUT_HASH", chunk, offset);
        case OP_PUT_HASH_WORD:
            return instruction_array_type_word(res, "PUT_HASH_WORD", chunk, offset);
        case OP_PUT_HASH_DWORD:
            return instruction_array_type_dword(res, "PUT_HASH_DWORD", chunk, offset);
        // case OP_PUT_BITSTRING:
        //     return instruction_array_type(res, "PUT_BITSTRING", chunk, offset);
        // case OP_PUT_BITSTRING_WORD:
        //     return instruction_array_type_word(res, "PUT_BITSTRING_WORD", chunk, offset);
        // case OP_PUT_BITSTRING_DWORD:
        //     return instruction_array_type_dword(res, "PUT_BITSTRING_DWORD", chunk, offset);

        // case OP_PUT_LABEL:
        //     return offset + ??;
        // case OP_GOTO:
        //     return offset + ??;
        // case OP_GOTO_LOCAL:
        //     return offset + ??;

        case OP_SET_GLOBAL:
            return instruction_variable(res, "SET_GLOBAL", chunk, offset);
        case OP_SET_GLOBAL_WORD:
            return instruction_variable_word(res, "SET_GLOBAL_WORD", chunk, offset);
        case OP_SET_GLOBAL_DWORD:
            return instruction_variable_dword(res, "SET_GLOBAL_DWORD", chunk, offset);
        case OP_SET_INSTANCE:
            return instruction_variable(res, "SET_INSTANCE", chunk, offset);
        case OP_SET_INSTANCE_WORD:
            return instruction_variable_word(res, "SET_INSTANCE_WORD", chunk, offset);
        case OP_SET_INSTANCE_DWORD:
            return instruction_variable_dword(res, "SET_INSTANCE_DWORD", chunk, offset);
        case OP_SET_LOCAL:
            return instruction_variable(res, "SET_LOCAL", chunk, offset);
        case OP_SET_LOCAL_WORD:
            return instruction_variable_word(res, "SET_LOCAL_WORD", chunk, offset);
        case OP_SET_LOCAL_DWORD:
            return instruction_variable_dword(res, "SET_LOCAL_DWORD", chunk, offset);

        case OP_GET_GLOBAL:
            return instruction_variable(res, "GET_GLOBAL", chunk, offset);
        case OP_GET_GLOBAL_WORD:
            return instruction_variable_word(res, "GET_GLOBAL_WORD", chunk, offset);
        case OP_GET_GLOBAL_DWORD:
            return instruction_variable_dword(res, "GET_GLOBAL_DWORD", chunk, offset);
        case OP_GET_INSTANCE:
            return instruction_variable(res, "GET_INSTANCE", chunk, offset);
        case OP_GET_INSTANCE_WORD:
            return instruction_variable_word(res, "GET_INSTANCE_WORD", chunk, offset);
        case OP_GET_INSTANCE_DWORD:
            return instruction_variable_dword(res, "GET_INSTANCE_DWORD", chunk, offset);
        case OP_GET_LOCAL:
            return instruction_variable(res, "GET_LOCAL", chunk, offset);
        case OP_GET_LOCAL_WORD:
            return instruction_variable_word(res, "GET_LOCAL_WORD", chunk, offset);
        case OP_GET_LOCAL_DWORD:
            return instruction_variable_dword(res, "GET_LOCAL_DWORD", chunk, offset);

        case OP_SEND:
            return instruction_send(res, "SEND", chunk, offset);
        case OP_SEND_WORD:
            return instruction_send_word(res, "SEND_WORD", chunk, offset);
        case OP_SEND_DWORD:
            return instruction_send_dword(res, "SEND_DWORD", chunk, offset);
        case OP_CLONE_OBJECT:
            return instruction_single(res, "CLONE_OBJECT", chunk, offset);
        case OP_BIND_METHOD:
            return instruction_single(res, "BIND_METHOD", chunk, offset);
        case OP_EXIT_ACTIVATION_RECORD:
            return instruction_single(res, "EXIT_ACTIVATION_RECORD", chunk, offset);

        case OP_PRIM_PUTS:
            return instruction_single(res, "PRIM_PUTS", chunk, offset);
        case OP_PRIM_1_MESSAGES:
            return instruction_single(res, "PRIM_1_MESSAGES", chunk, offset);
        case OP_PRIM_2_OBJECT_ID:
            return instruction_single(res, "PRIM_2_OBJECT_ID", chunk, offset);
        case OP_PRIM_3_TO_STRING:
            return instruction_single(res, "PRIM_3_TO_STRING", chunk, offset);
        case OP_PRIM_4_EQUALS:
            return instruction_single(res, "PRIM_4_EQUALS", chunk, offset);
        case OP_PRIM_5_EQUALS_NUMERIC:
            return instruction_single(res, "PRIM_5_EQUALS_NUMERIC", chunk, offset);

        case OP_PRIM_PROC_CALL:
            return instruction_single(res, "PRIM_PROC_CALL", chunk, offset);
        case OP_PRIM_PROC_CALL_PARAMS:
            return instruction_single(res, "PRIM_PROC_CALL_PARAMS", chunk, offset);

        case OP_PRIM_NUMERIC_ADD:
            return instruction_single(res, "PRIM_NUMERIC_ADD", chunk, offset);
        case OP_PRIM_NUMERIC_SUB:
            return instruction_single(res, "PRIM_NUMERIC_SUB", chunk, offset);
        case OP_PRIM_NUMERIC_MUL:
            return instruction_single(res, "PRIM_NUMERIC_MUL", chunk, offset);
        case OP_PRIM_NUMERIC_DIV:
            return instruction_single(res, "PRIM_NUMERIC_DIV", chunk, offset);
        case OP_PRIM_NUMERIC_ABS:
            return instruction_single(res, "PRIM_NUMERIC_ABS", chunk, offset);
        case OP_PRIM_NUMERIC_EQUALS:
            return instruction_single(res, "PRIM_NUMERIC_EQUALS", chunk, offset);
        case OP_PRIM_NUMERIC_LT:
            return instruction_single(res, "PRIM_NUMERIC_LT", chunk, offset);
        case OP_PRIM_NUMERIC_GT:
            return instruction_single(res, "PRIM_NUMERIC_GT", chunk, offset);
        case OP_PRIM_NUMERIC_LTE:
            return instruction_single(res, "PRIM_NUMERIC_LTE", chunk, offset);
        case OP_PRIM_NUMERIC_GTE:
            return instruction_single(res, "PRIM_NUMERIC_GTE", chunk, offset);
        case OP_PRIM_INTEGER_INCR:
            return instruction_single(res, "PRIM_INTEGER_INCR", chunk, offset);
        case OP_PRIM_INTEGER_DECR:
            return instruction_single(res, "PRIM_INTEGER_DECR", chunk, offset);
        case OP_PRIM_INTEGER_DOUBLE:
            return instruction_single(res, "PRIM_INTEGER_DOUBLE", chunk, offset);

        default: {
            string *unknown_opcode = string_new("");
            string_addf(unknown_opcode, "Unknown opcode %d", instruction);
            vector_add(res, unknown_opcode);
            return offset + 1;
        }
    }
}

vector *inspect_vm_bytecode(VM *vm) {
    vector *res = vector_new_empty();

    size_t number_of_bytecodes = chunk_size(vm->current->bytecode);
    for(size_t offset = 0; offset < number_of_bytecodes;)
        offset = inspect_instruction(res, vm->current->bytecode, offset);

    return res;
}

void inspect_and_print_vm_bytecode(VM *vm) {
    vector *disassembled = inspect_vm_bytecode(vm);

    size_t disassembled_size = vector_size(disassembled);
    for(size_t i = 0; i < disassembled_size; i++)
        printf("%s\n", string_get(vector_get(disassembled, i)));
}

void inspect_and_print_proc(VM *vm) {
    printf("\n/-------------- Disassembly: <proc> ------------\\\n");
    inspect_and_print_vm_bytecode(vm);
    printf("\\-----------------------------------------------/\n\n");
}

void inspect_and_print_method(VM *vm) {
    printf("\n/--------------- Disassembly: < #%s > ---------\\\n", AS_STRING(vm->current->bound_method->message_name)->chars);
    inspect_and_print_vm_bytecode(vm);
    printf("\\-----------------------------------------------/\n\n");
}

void inspect_and_print_main(VM *vm) {
    printf("\n/-------------- Disassembly: < $Margaret#main: > ------------\\\n");
    inspect_and_print_vm_bytecode(vm);
    printf("\\-----------------------------------------------/\n\n");
}
