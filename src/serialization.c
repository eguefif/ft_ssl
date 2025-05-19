#include "ft_ssl_types.h"

// Len is the output size
void charToU32Array(u32 *output, u8 *input, u64 len) {
    u64 i, j;
    for (i = 0, j = 0; i < len; i++, j += 4) {
        output[i] = ((u32)input[j]) | (((u32)input[j + 1]) << 8) |
                    (((u32)input[j + 2]) << 16) | (((u32)input[j + 3]) << 24);
    }
}

// Len is the input size
void u32ArrayToChar(u8 *output, u32 *input, u64 len) {
    u64 i, j;
    for (i = 0, j = 0; j < len; j++, i += 4) {
        output[i] = (unsigned char)(input[j] & 0xFF);
        output[i + 1] = (unsigned char)((input[j] >> 8) & 0xFF);
        output[i + 2] = (unsigned char)((input[j] >> 16) & 0xFF);
        output[i + 3] = (unsigned char)((input[j] >> 24) & 0xFF);
    }
}
