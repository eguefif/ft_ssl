#include "ft_ssl.h"

void u32ArrayToChar(u8 *output, u32 *input, u64 len);

void round1op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round2op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round3op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round4op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round1(u32 *, u32 *, u32 *, u32 *, u32 *);
void round2(u32 *, u32 *, u32 *, u32 *, u32 *);
void round3(u32 *, u32 *, u32 *, u32 *, u32 *);
void round4(u32 *, u32 *, u32 *, u32 *, u32 *);
void processStates(MD5Data *data);
void encode(u32 *output, char *input, u64 len);

MD5Data md5Init() {
    MD5Data data;

    data.states[0] = 0x67452301;
    data.states[1] = 0xefcdab89;
    data.states[2] = 0x98badcfe;
    data.states[3] = 0x10325476;
    bzero(data.buffer, 64);
    data.bitsCount = 0;

    return data;
}

void md5Update(MD5Data *data, u8 *input, u64 inputLen) {
    u64 i = 0;

    data->bitsCount += inputLen * 8;
    if (inputLen > 64) {
        for (i = 0; i < (inputLen - 64); i += 64) {
            strncpy((char *)data->buffer, (char *)&input[i], 64);
            processStates(data);
        }
    } else
        i = 0;

    data->index = inputLen - i;
    strncpy((char *)data->buffer, (char *)&input[i], inputLen - i);
}

void md5Finalize(MD5Data *data, u8 *digest) {
    memset(&data->buffer[data->index], 0, 64 - data->index);
    int remaining = 64 - data->index;
    if (remaining > 0 && remaining < 9) {
        data->buffer[data->index] = 0x80;
        u32 length[2];
        processStates(data);
        memset(data->buffer, 0, 64);
        length[0] = data->bitsCount & 0xFFFF;
        length[1] = (data->bitsCount >> 32) & 0xFFFF;
        u32ArrayToChar(&data->buffer[56], length, 2);
        processStates(data);
        u32ArrayToChar(digest, data->states, 4);
    } else {
        data->buffer[data->index] = 0x80;
        u32 length[2];
        length[0] = data->bitsCount & 0xFFFF;
        length[1] = (data->bitsCount >> 32) & 0xFFFF;
        u32ArrayToChar(&data->buffer[56], length, 2);
        processStates(data);
        u32ArrayToChar(digest, data->states, 4);
    }
}

void charToU32Array(u32 *output, u8 *input, u64 len) {
    u64 i, j;
    for (i = 0, j = 0; i < len; i++, j += 4) {
        output[i] = ((u32)input[j]) | (((u32)input[j + 1]) << 8) |
                    (((u32)input[j + 2]) << 16) | (((u32)input[j + 3]) << 24);
    }
}

void u32ArrayToChar(u8 *output, u32 *input, u64 len) {
    u64 i, j;
    for (i = 0, j = 0; j < len; j++, i += 4) {
        output[i] = (unsigned char)(input[j] & 0xFF);
        output[i + 1] = (unsigned char)((input[j] >> 8) & 0xFF);
        output[i + 2] = (unsigned char)((input[j] >> 16) & 0xFF);
        output[i + 3] = (unsigned char)((input[j] >> 24) & 0xFF);
    }
}

void processStates(MD5Data *data) {
    u32 block[16];
    charToU32Array(block, data->buffer, 16);
    u32 a = data->states[0];
    u32 b = data->states[1];
    u32 c = data->states[2];
    u32 d = data->states[3];

    round1(&a, &b, &c, &d, block);
    round2(&a, &b, &c, &d, block);
    round3(&a, &b, &c, &d, block);
    round4(&a, &b, &c, &d, block);

    data->states[0] += a;
    data->states[1] += b;
    data->states[2] += c;
    data->states[3] += d;
}

void round1(u32 *a, u32 *b, u32 *c, u32 *d, u32 *block) {
    round1op(a, *b, *c, *d, 0, S11, 1, block);
    round1op(d, *a, *b, *c, 1, S12, 2, block);
    round1op(c, *d, *a, *b, 2, S13, 3, block);
    round1op(b, *c, *d, *a, 3, S14, 4, block);

    round1op(a, *b, *c, *d, 4, S11, 5, block);
    round1op(d, *a, *b, *c, 5, S12, 6, block);
    round1op(c, *d, *a, *b, 6, S13, 7, block);
    round1op(b, *c, *d, *a, 7, S14, 8, block);

    round1op(a, *b, *c, *d, 8, S11, 9, block);
    round1op(d, *a, *b, *c, 9, S12, 10, block);
    round1op(c, *d, *a, *b, 10, S13, 11, block);
    round1op(b, *c, *d, *a, 11, S14, 12, block);

    round1op(a, *b, *c, *d, 12, S11, 13, block);
    round1op(d, *a, *b, *c, 13, S12, 14, block);
    round1op(c, *d, *a, *b, 14, S13, 15, block);
    round1op(b, *c, *d, *a, 15, S14, 16, block);
}

void round1op(u32 *a, u32 b, u32 c, u32 d, u32 k, u32 s, u32 i, u32 *block) {
    *a += F(b, c, d) + block[k] + SINE_TABLE[i - 1];
    *a = ROTATE_LEFT(*a, s);
    *a += b;
}

void round2(u32 *a, u32 *b, u32 *c, u32 *d, u32 *block) {
    round2op(a, *b, *c, *d, 1, S21, 17, block);
    round2op(d, *a, *b, *c, 6, S22, 18, block);
    round2op(c, *d, *a, *b, 11, S23, 19, block);
    round2op(b, *c, *d, *a, 0, S24, 20, block);

    round2op(a, *b, *c, *d, 5, S21, 21, block);
    round2op(d, *a, *b, *c, 10, S22, 22, block);
    round2op(c, *d, *a, *b, 15, S23, 23, block);
    round2op(b, *c, *d, *a, 4, S24, 24, block);

    round2op(a, *b, *c, *d, 9, S21, 25, block);
    round2op(d, *a, *b, *c, 14, S22, 26, block);
    round2op(c, *d, *a, *b, 3, S23, 27, block);
    round2op(b, *c, *d, *a, 8, S24, 28, block);

    round2op(a, *b, *c, *d, 13, S21, 29, block);
    round2op(d, *a, *b, *c, 2, S22, 30, block);
    round2op(c, *d, *a, *b, 7, S23, 31, block);
    round2op(b, *c, *d, *a, 12, S24, 32, block);
}

void round2op(u32 *a, u32 b, u32 c, u32 d, u32 k, u32 s, u32 i, u32 *block) {
    *a += G(b, c, d) + block[k] + SINE_TABLE[i - 1];
    *a = ROTATE_LEFT(*a, s);
    *a += b;
}

void round3(u32 *a, u32 *b, u32 *c, u32 *d, u32 *block) {
    round3op(a, *b, *c, *d, 5, S31, 33, block);
    round3op(d, *a, *b, *c, 8, S32, 34, block);
    round3op(c, *d, *a, *b, 11, S33, 35, block);
    round3op(b, *c, *d, *a, 14, S34, 36, block);

    round3op(a, *b, *c, *d, 1, S31, 37, block);
    round3op(d, *a, *b, *c, 4, S32, 38, block);
    round3op(c, *d, *a, *b, 7, S33, 39, block);
    round3op(b, *c, *d, *a, 10, S34, 40, block);

    round3op(a, *b, *c, *d, 13, S31, 41, block);
    round3op(d, *a, *b, *c, 0, S32, 42, block);
    round3op(c, *d, *a, *b, 3, S33, 43, block);
    round3op(b, *c, *d, *a, 6, S34, 44, block);

    round3op(a, *b, *c, *d, 9, S31, 45, block);
    round3op(d, *a, *b, *c, 12, S32, 46, block);
    round3op(c, *d, *a, *b, 15, S33, 47, block);
    round3op(b, *c, *d, *a, 2, S34, 48, block);
}

void round3op(u32 *a, u32 b, u32 c, u32 d, u32 k, u32 s, u32 i, u32 *block) {
    *a += H(b, c, d) + block[k] + SINE_TABLE[i - 1];
    *a = ROTATE_LEFT(*a, s);
    *a += b;
}

void round4(u32 *a, u32 *b, u32 *c, u32 *d, u32 *block) {
    round4op(a, *b, *c, *d, 0, S41, 49, block);
    round4op(d, *a, *b, *c, 7, S42, 50, block);
    round4op(c, *d, *a, *b, 14, S43, 51, block);
    round4op(b, *c, *d, *a, 5, S44, 52, block);

    round4op(a, *b, *c, *d, 12, S41, 53, block);
    round4op(d, *a, *b, *c, 3, S42, 54, block);
    round4op(c, *d, *a, *b, 10, S43, 55, block);
    round4op(b, *c, *d, *a, 1, S44, 56, block);

    round4op(a, *b, *c, *d, 8, S41, 57, block);
    round4op(d, *a, *b, *c, 15, S42, 58, block);
    round4op(c, *d, *a, *b, 6, S43, 59, block);
    round4op(b, *c, *d, *a, 13, S44, 60, block);

    round4op(a, *b, *c, *d, 4, S41, 61, block);
    round4op(d, *a, *b, *c, 11, S42, 62, block);
    round4op(c, *d, *a, *b, 2, S43, 63, block);
    round4op(b, *c, *d, *a, 9, S44, 64, block);
}

void round4op(u32 *a, u32 b, u32 c, u32 d, u32 k, u32 s, u32 i, u32 *block) {
    *a += I(b, c, d) + block[k] + SINE_TABLE[i - 1];
    *a = ROTATE_LEFT(*a, s);
    *a += b;
}
