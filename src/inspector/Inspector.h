#ifndef __INSPECTOR_H_
#define __INSPECTOR_H_

#include "../base/marg_vector.h"

/**
 * @brief Inspects an instruction inside of a chunk
 * @param res -> Adds log information to the res vector
 * @param chunk -> The chunk from which bytecodes are to be inspected
 * @param offset -> The current offset of the bytecode in the array
 * @return size_t -> The newly calculated offset
 */
size_t inspect_instruction(marg_vector *res, Chunk *chunk, size_t offset);

/**
 * @brief Disassembles a bytecode chunk and inspects the content
 * @param chunk -> The chunk to be disassembled
 */
marg_vector *inspect_chunk(Chunk *chunk);

#endif
