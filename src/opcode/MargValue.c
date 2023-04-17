#include "MargValue.h"

#include "../base/memory.h"

marg_string *marg_value_format(MargValue self) {
    marg_string *res = marg_string_new("");
    marg_string_addf(res, "%g", self);
    return res;
}

uint8_t *long_constant_to_bytes(uint32_t constant) {
    uint8_t *res = (uint8_t*)collected_malloc(sizeof(uint8_t) * 4);

    uint16_t first = (constant >> 16) & 0xffff;
    uint16_t second = constant & 0xffff;

    res[0] = (first >> 8) & 0xff;
    res[1] = first & 0xff;
    res[2] = (second >> 8) & 0xff;
    res[3] = second & 0xff;

    return res;
}

uint32_t bytes_to_long_constant(uint8_t *bytes) {
    return ((bytes[0] << 8) | bytes[1] << 8) | (bytes[2] << 8) | bytes[3];
}
