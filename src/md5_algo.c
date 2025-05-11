#include "ft_ssl.h"

u32 SINE_TABLE[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
    0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
    0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
    0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
    0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
    0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define S11 7
#define S12 12
#define S13 17
#define S14 22

#define S21 5
#define S22 9
#define S23 14
#define S24 20

#define S31 4
#define S32 11
#define S33 16
#define S34 23

#define S41 6
#define S42 10
#define S43 15
#define S44 21

void round1op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round2op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round3op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round4op(u32 *, u32, u32, u32, u32, u32, u32, u32 *);
void round1(u32 *, u32 *, u32 *, u32 *, u32 *);
void round2(u32 *, u32 *, u32 *, u32 *, u32 *);
void round3(u32 *, u32 *, u32 *, u32 *, u32 *);
void round4(u32 *, u32 *, u32 *, u32 *, u32 *);
void processStates(u32 *states, u32 *block);

void makeDigestFromPaddedTarget(char *digest, MD5Data *data) {
    assert(data->paddedTargetSize * 8 % 512 == 0);
    bzero(digest, 16);
    u32 states[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    u32 block[32] = {0};
    u32 *targetByWords = (u32 *)data->target;
    for (u64 i = 0; i < data->paddedTargetSize / 2; i += 16) {
        for (u64 j = 0; j < 16; j++) {
            block[j] = data->target[i * 16 + j];
        }
        processStates(states, block);
    }
    makeOutput(digest, states);
}

void processStates(u32 *states, u32 *block) {
    u32 a = states[0];
    u32 b = states[1];
    u32 c = states[2];
    u32 d = states[3];

    round1(&a, &b, &c, &d, block);
    round2(&a, &b, &c, &d, block);
    round3(&a, &b, &c, &d, block);
    round4(&a, &b, &c, &d, block);

    states[0] += a;
    states[1] += b;
    states[2] += c;
    states[3] += d;
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
    *a += F(b, c, d) + block[k] + SINE_TABLE[i];
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
    *a += G(b, c, d) + block[k] + SINE_TABLE[i];
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
    *a += H(b, c, d) + block[k] + SINE_TABLE[i];
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
    *a += I(b, c, d) + block[k] + SINE_TABLE[i];
    *a = ROTATE_LEFT(*a, s);
    *a += b;
}

void makeOutput(char *digest, u32 *states) {
    for (u8 i = 0; i < 4; i++) {
        u16 lower = (u16)(states[i] & 0xFFFF);
        u16 higher = (u16)((states[i] & 0xFFFF0000) >> 16);
        sprintf(digest + i * 8, "%04x%04x", lower, higher);
    }
}
