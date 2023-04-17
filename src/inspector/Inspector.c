#include "Inspector.h"

#include "../base/marg_string.h"

#include "../opcode/Opcodes.h"

/**
 * @brief Disassembles a simple instruction (offset size: 1)
 * @param res -> Adds log information to the res vector
 * @param name -> Name of opcode
 * @param chunk -> Current chunk
 * @param offset -> Current offset
 * @return size_t -> Newly calculated offset
 */
static size_t simple_instruction(marg_vector *res, const char *name, Chunk *chunk, int offset) {
    uint8_t opcode = chunk_get(chunk, offset);

    marg_string *disassembled_instruction = marg_string_new("");
    marg_string_addf(disassembled_instruction, "%04zx    ", offset);
    marg_string_addf(disassembled_instruction, "%02x          ", opcode);
    marg_string_addf(disassembled_instruction, "%s", name);
    marg_vector_add(res, disassembled_instruction);

    return offset + 1;
}

static int constant_instruction(marg_vector *res, const char *name, Chunk *chunk, int offset) {
    uint8_t opcode = chunk_get(chunk, offset);
    uint8_t constant = chunk_get(chunk, offset + 1);

    marg_string *disassembled_instruction = marg_string_new("");
    marg_string_addf(disassembled_instruction, "%04zx    ", offset);
    marg_string_addf(disassembled_instruction, "%02x %02x       ", opcode, constant);
    marg_string_addf(disassembled_instruction, "%-16s %d (", name, constant);
    marg_string_add(disassembled_instruction, marg_value_format(chunk_get_constant(chunk, constant)));
    marg_string_add_str(disassembled_instruction, ")");
    marg_vector_add(res, disassembled_instruction);

    return offset + 2;
}

size_t inspect_instruction(marg_vector *res, Chunk *chunk, size_t offset) {
    uint8_t instruction = chunk_get(chunk, offset);
    switch(instruction) {
        case OP_RETURN:
            return simple_instruction(res, "RETURN", chunk, offset);
        case OP_CONSTANT:
            return constant_instruction(res, "CONSTANT", chunk, offset);
        case OP_NIL:
            return simple_instruction(res, "NIL", chunk, offset);
        case OP_TRUE:
            return simple_instruction(res, "TRUE", chunk, offset);
        case OP_FALSE:
            return simple_instruction(res, "FALSE", chunk, offset);
        default: {
            marg_string *unknown_opcode = marg_string_new("");
            marg_string_addf(unknown_opcode, "Unknown opcode %d", instruction);
            marg_vector_add(res, unknown_opcode);
            return offset + 1;
        }
    }
}

marg_vector *inspect_chunk(Chunk *chunk) {
    marg_vector *res = marg_vector_new_empty();

    size_t number_of_bytecodes = chunk_size(chunk);
    for(size_t offset = 0; offset < number_of_bytecodes;)
        offset = inspect_instruction(res, chunk, offset);

    return res;
}
