#include "Inspector.h"

#include <stdio.h>

#include "../base/marg_string.h"

#include "../opcode/Opcodes.h"

static void write_offset_and_line_number_on(marg_string *disassembled_instruction, Chunk *chunk, size_t offset) {
    marg_string_addf(disassembled_instruction, "%04zx    ", offset);
    if(offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1])
        marg_string_add_str(disassembled_instruction, "     |      ");
    else
        marg_string_addf(disassembled_instruction, "%6zu      ", chunk->lines[offset]);
}

/**
 * @brief Disassembles a simple instruction
 * @param res -> Adds log information to the res vector
 * @param name -> Name of opcode
 * @param chunk -> Current chunk
 * @param offset -> Current offset
 * @return size_t -> Newly calculated offset
 */
static size_t instruction_offset_1(marg_vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);

    marg_string *disassembled_instruction = marg_string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    marg_string_addf(disassembled_instruction, "%02x                  ", opcode);
    marg_string_addf(disassembled_instruction, "%s", name);
    marg_vector_add(res, disassembled_instruction);

    return offset + 1;
}

static size_t instruction_offset_2(marg_vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t constant = chunk_get(chunk, offset + 1);

    marg_string *disassembled_instruction = marg_string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    marg_string_addf(disassembled_instruction, "%02x %02x               ", opcode, constant);
    marg_string_addf(disassembled_instruction, "%-16s %d (", name, constant);
    marg_string_add(disassembled_instruction, marg_value_format(chunk_get_constant(chunk, constant)));
    marg_string_add_str(disassembled_instruction, ")");
    marg_vector_add(res, disassembled_instruction);

    return offset + 2;
}

static size_t instruction_offset_5(marg_vector *res, const char *name, Chunk *chunk, size_t offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t bytes[4] = {
        chunk_get(chunk, offset + 1),
        chunk_get(chunk, offset + 2),
        chunk_get(chunk, offset + 3),
        chunk_get(chunk, offset + 4),
    };
    uint32_t constant = bytes_to_long_constant(bytes);

    marg_string *disassembled_instruction = marg_string_new("");
    write_offset_and_line_number_on(disassembled_instruction, chunk, offset);
    marg_string_addf(disassembled_instruction, "%02x %02x %02x %02x %02x      ", opcode, chunk_get(chunk, offset + 1), bytes[1], bytes[2], bytes[3]);
    marg_string_addf(disassembled_instruction, "%-16s %d (", name, constant);
    marg_string_add(disassembled_instruction, marg_value_format(chunk_get_constant(chunk, constant)));
    marg_string_add_str(disassembled_instruction, ")");
    marg_vector_add(res, disassembled_instruction);

    return offset + 5;
}

/**
 * @brief Inspects an instruction inside of a chunk
 * @param res -> Adds log information to the res vector
 * @param chunk -> The chunk from which bytecodes are to be inspected
 * @param offset -> The current offset of the bytecode in the array
 * @return size_t -> The newly calculated offset
 */
static size_t inspect_instruction(marg_vector *res, Chunk *chunk, size_t offset) {
    uint8_t instruction = chunk_get(chunk, offset);
    switch(instruction) {
        case OP_RETURN:
            return instruction_offset_1(res, "RETURN", chunk, offset);
        case OP_CONSTANT:
            return instruction_offset_2(res, "CONSTANT", chunk, offset);
        case OP_LONG_CONSTANT:
            return instruction_offset_5(res, "LONG_CONSTANT", chunk, offset);
        case OP_NIL:
            return instruction_offset_1(res, "NIL", chunk, offset);
        case OP_TRUE:
            return instruction_offset_1(res, "TRUE", chunk, offset);
        case OP_FALSE:
            return instruction_offset_1(res, "FALSE", chunk, offset);
        default: {
            marg_string *unknown_opcode = marg_string_new("");
            marg_string_addf(unknown_opcode, "Unknown opcode %d", instruction);
            marg_vector_add(res, unknown_opcode);
            return offset + 1;
        }
    }
}

marg_vector *inspect_vm_bytecode(VM *vm) {
    marg_vector *res = marg_vector_new_empty();

    size_t number_of_bytecodes = chunk_size(vm->bytecode);
    for(size_t offset = 0; offset < number_of_bytecodes;)
        offset = inspect_instruction(res, vm->bytecode, offset);

    return res;
}

void inspect_and_print_vm_bytecode(VM *vm) {
    marg_vector *disassembled = inspect_vm_bytecode(vm);

    size_t disassembled_size = marg_vector_size(disassembled);
    for(size_t i = 0; i < disassembled_size; i++)
        printf("%s\n", marg_string_get(marg_vector_get(disassembled, i)));
}
