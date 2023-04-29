#include "byte_conversions.h"

#include "../base/memory.h"

uint8_t *word_to_bytes(uint16_t word) {
    uint8_t *bytes = (uint8_t*)collected_malloc(sizeof(uint8_t) * 2);

    bytes[0] = (word >> 8) & 0xff;
    bytes[1] = word & 0xff;

    return bytes;
}

uint8_t *dword_to_bytes(uint32_t dword) {
    uint8_t *bytes = (uint8_t*)collected_malloc(sizeof(uint8_t) * 4);

    uint8_t *lhs_bytes = word_to_bytes((dword >> 16) & 0xffff);
    uint8_t *rhs_bytes = word_to_bytes(dword & 0xffff);

    bytes[0] = lhs_bytes[0];
    bytes[1] = lhs_bytes[1];

    bytes[2] = rhs_bytes[0];
    bytes[3] = rhs_bytes[1];

    return bytes;
}

uint8_t *qword_to_bytes(uint64_t qword) {
    uint8_t *bytes = (uint8_t*)collected_malloc(sizeof(uint8_t) * 8);

    uint8_t *lhs_bytes = dword_to_bytes((qword >> 32) & 0xffffffff);
    uint8_t *rhs_bytes = dword_to_bytes(qword & 0xffffffff);

    bytes[0] = lhs_bytes[0];
    bytes[1] = lhs_bytes[1];
    bytes[2] = lhs_bytes[2];
    bytes[3] = lhs_bytes[3];

    bytes[4] = rhs_bytes[0];
    bytes[5] = rhs_bytes[1];
    bytes[6] = rhs_bytes[2];
    bytes[7] = rhs_bytes[3];

    return bytes;
}

uint16_t bytes_to_word(uint8_t *bytes) {
    return (uint16_t)bytes[0] << 8
         | bytes[1];
}

uint32_t bytes_to_dword(uint8_t *bytes) {
    return (uint32_t)bytes[0] << 24
         | (uint32_t)bytes[1] << 16
         | (uint16_t)bytes[2] << 8
         | bytes[3];
}

uint64_t bytes_to_qword(uint8_t *bytes) {
    return (uint64_t)bytes[0] << 56
         | (uint64_t)bytes[1] << 48
         | (uint64_t)bytes[2] << 40
         | (uint64_t)bytes[3] << 32
         | (uint32_t)bytes[4] << 24
         | (uint32_t)bytes[5] << 16
         | (uint16_t)bytes[6] << 8
         | bytes[7];
}
