#include "Inspector.h"

#include <stdio.h> /* printf */
#include <string.h> /* strcmp */

#include "../base/string.h"
#include "../base/Chunk.h"

#include "../opcode/Opcodes.h"

static void write_offset_and_line_number_on(string *disassembled_instruction, Chunk *chunk, size_t offset) {
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
static size_t instruction_single(vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x                  ", opcode);
    string_addf(disassembled_instruction, "%s", name);
    vector_add(res, disassembled_instruction);

    return offset + 1;
}

static size_t instruction_constant(vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t constant = chunk_get(chunk, offset + 1);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x               ", opcode, constant);
    string_addf(disassembled_instruction, "%-24s %d (", name, constant);
    string_add(disassembled_instruction, marg_value_format(chunk_constant_get(chunk, constant)));
    string_add_str(disassembled_instruction, ")");
    vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_variable(vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t variable = chunk_get(chunk, offset + 1);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x               ", opcode, variable);
    string_addf(disassembled_instruction, "%-24s %d (", name, variable);
    if(!strcmp(name, "SET_GLOBAL")
    || !strcmp(name, "GET_GLOBAL")) {
        string_add_str(disassembled_instruction, "$");
    }
    else if(!strcmp(name, "SET_INSTANCE")
         || !strcmp(name, "GET_INSTANCE")
    ) {
        string_add_str(disassembled_instruction, "@");
    }
    string_add(disassembled_instruction, marg_value_as_variable(chunk_constant_get(chunk, variable)));
    string_add_str(disassembled_instruction, ")");
    vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_long_variable(vector *res, const char *name, Chunk *chunk, size_t offset) {
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
    string_addf(disassembled_instruction, "%-24s %d (", name, variable);
    if(!strcmp(name, "SET_GLOBAL_LONG")
    || !strcmp(name, "GET_GLOBAL_LONG")) {
        string_add_str(disassembled_instruction, "$");
    }
    else if(!strcmp(name, "SET_INSTANCE_LONG")
         || !strcmp(name, "GET_INSTANCE_LONG")
    ) {
        string_add_str(disassembled_instruction, "@");
    }
    string_add(disassembled_instruction, marg_value_as_variable(chunk_constant_get(chunk, variable)));
    string_add_str(disassembled_instruction, ")");
    vector_add(res, disassembled_instruction);

    return offset + 5;
}

static size_t instruction_long_constant(vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[4] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
        chunk_get(chunk, offset + 3),
        chunk_get(chunk, offset + 4),
    };
    uint32_t constant = bytes_to_dword(bytes);

    string *disassembled_instruction = string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, chunk_get(chunk, offset + 1), bytes[1], bytes[2], bytes[3]);
    string_addf(disassembled_instruction, "%-24s %d (", name, constant);
    string_add(disassembled_instruction, marg_value_format(chunk_constant_get(chunk, constant)));
    string_add_str(disassembled_instruction, ")");
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
static size_t inspect_instruction(vector *res, Chunk *chunk, size_t offset) {
    uint8_t instruction = chunk_get(chunk, offset);
    switch(instruction) {
        case TEST_OP_PRINT:
            return instruction_single(res, "PRINT", chunk, offset);

        case OP_RETURN:
            return instruction_single(res, "RETURN", chunk, offset);

        case OP_PUT_NIL:
            return instruction_single(res, "PUT_NIL", chunk, offset);
        case OP_PUT_TRUE:
            return instruction_single(res, "PUT_TRUE", chunk, offset);
        case OP_PUT_FALSE:
            return instruction_single(res, "PUT_FALSE", chunk, offset);

        case OP_PUT_OBJECT:
            return instruction_constant(res, "PUT_OBJECT", chunk, offset);
        case OP_PUT_OBJECT_LONG:
            return instruction_long_constant(res, "PUT_OBJECT_LONG", chunk, offset);

        case OP_POP:
            return instruction_single(res, "POP", chunk, offset);

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

    size_t number_of_bytecodes = chunk_size(vm->bytecode);
    for(size_t offset = 0; offset < number_of_bytecodes;)
        offset = inspect_instruction(res, vm->bytecode, offset);

    return res;
}

void inspect_and_print_vm_bytecode(VM *vm) {
    vector *disassembled = inspect_vm_bytecode(vm);

    size_t disassembled_size = vector_size(disassembled);
    for(size_t i = 0; i < disassembled_size; i++)
        printf("%s\n", string_get(vector_get(disassembled, i)));
}
