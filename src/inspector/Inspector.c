#include "Inspector.h"

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "../base/string.h"
#include "../base/chunk.h"

#include "../opcode/Opcodes.h"
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

static size_t instruction_long_object(vector *res, char *name, chunk *chunk, size_t offset) {
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
    string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, chunk_get(chunk, offset + 1), bytes[1], bytes[2], bytes[3]);
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

static size_t instruction_long_variable(vector *res, char *name, chunk *chunk, size_t offset) {
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

static size_t instruction_long_array_type(vector *res, char *name, chunk *chunk, size_t offset) {
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
        case OP_POP:
            return instruction_single(res, "POP", chunk, offset);
        case TEST_OP_PRINT:
            return instruction_single(res, "PRINT", chunk, offset);

        case OP_HALT:
            return instruction_single(res, "HALT", chunk, offset);

        case OP_PUT_NIL:
            return instruction_single(res, "PUT_NIL", chunk, offset);
        case OP_PUT_TRUE:
            return instruction_single(res, "PUT_TRUE", chunk, offset);
        case OP_PUT_FALSE:
            return instruction_single(res, "PUT_FALSE", chunk, offset);
        
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
        case OP_PUT_OBJECT_LONG:
            return instruction_long_object(res, "PUT_OBJECT_LONG", chunk, offset);

        case OP_PUT_TENSOR:
            return instruction_array_type(res, "PUT_TENSOR", chunk, offset);
        case OP_PUT_TENSOR_LONG:
            return instruction_long_array_type(res, "PUT_TENSOR_LONG", chunk, offset);
        case OP_PUT_HASH:
            return instruction_array_type(res, "PUT_HASH", chunk, offset);
        case OP_PUT_HASH_LONG:
            return instruction_long_array_type(res, "PUT_HASH_LONG", chunk, offset);

        case OP_SET_GLOBAL:
            return instruction_variable(res, "SET_GLOBAL", chunk, offset);
        case OP_SET_GLOBAL_LONG:
            return instruction_long_variable(res, "SET_GLOBAL_LONG", chunk, offset);
        case OP_SET_INSTANCE:
            return instruction_variable(res, "SET_INSTANCE", chunk, offset);
        case OP_SET_INSTANCE_LONG:
            return instruction_long_variable(res, "SET_INSTANCE_LONG", chunk, offset);
        case OP_SET_LOCAL:
            return instruction_variable(res, "SET_LOCAL", chunk, offset);
        case OP_SET_LOCAL_LONG:
            return instruction_long_variable(res, "SET_LOCAL_LONG", chunk, offset);

        case OP_GET_GLOBAL:
            return instruction_variable(res, "GET_GLOBAL", chunk, offset);
        case OP_GET_GLOBAL_LONG:
            return instruction_long_variable(res, "GET_GLOBAL_LONG", chunk, offset);
        case OP_GET_INSTANCE:
            return instruction_variable(res, "GET_INSTANCE", chunk, offset);
        case OP_GET_INSTANCE_LONG:
            return instruction_long_variable(res, "GET_INSTANCE_LONG", chunk, offset);
        case OP_GET_LOCAL:
            return instruction_variable(res, "GET_LOCAL", chunk, offset);
        case OP_GET_LOCAL_LONG:
            return instruction_long_variable(res, "GET_LOCAL_LONG", chunk, offset);

        case OP_CALL_PROC:
            return instruction_single(res, "CALL_PROC", chunk, offset);
        case OP_CALL_PROC_PARAMS:
            return instruction_single(res, "CALL_PROC_PARAMS", chunk, offset);
        case OP_EXIT_ACTIVATION_RECORD:
            return instruction_single(res, "EXIT_ACTIVATION_RECORD", chunk, offset);


        case OP_BIND_METHOD:
            return instruction_single(res, "BIND_METHOD", chunk, offset);

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
    printf("\n/--------------- Disassembly: < %s#%s > ---------\\\n", vm->current->bound_method->bound_object->name, AS_STRING(vm->current->bound_method->message_name)->chars);
    inspect_and_print_vm_bytecode(vm);
    printf("\\-----------------------------------------------/\n\n");
}

void inspect_and_print_main(VM *vm) {
    printf("\n/-------------- Disassembly: <MAIN> ------------\\\n");
    inspect_and_print_vm_bytecode(vm);
    printf("\\-----------------------------------------------/\n\n");
}
