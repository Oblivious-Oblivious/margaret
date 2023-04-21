#include "alternate_to_dec.h"

#include "memory.h"

#include <stdio.h>  /* snprintf */
#include <stdlib.h> /* uint64_t */
#include <string.h> /* strlen */
#include <math.h>   /* ceil, log10 */

static char *__int_to_str(uint64_t dec) {
    int len = (int)((ceil(log10(dec)) + 1) * sizeof(char));
    char *res = (char*)collected_malloc(sizeof(char) * len);
    snprintf(res, len, "%lld", dec);
    return res;
}

char *bin_to_dec(char *bin) {
    uint64_t dec = 0;
    int len = strlen(bin);

    for(int i = 0; i < len; i++)
        dec = dec * 2 + (bin[i] - '0');

    return __int_to_str(dec);
}

char *oct_to_dec(char *oct) {
    uint64_t dec = 0;
    int len = strlen(oct);

    for(int i = 0; i < len; i++)
        dec = dec * 8 + (oct[i] - '0');

    return __int_to_str(dec);
}

char *hex_to_dec(char *hex) {
    uint64_t dec = 0;
    int len = strlen(hex);

    for(int i = 0; i < len; i++) {
        if(hex[i] >= '0' && hex[i] <= '9')
            dec = dec * 16 + hex[i] - '0';
        else if(hex[i] >= 'A' && hex[i] <= 'Z')
            dec = dec * 16 + hex[i] - 'A' + 10;
        else if(hex[i] >= 'a' && hex[i] <= 'z')
            dec = dec * 16 + hex[i] - 'a' + 10;
    }

    return __int_to_str(dec);
}
