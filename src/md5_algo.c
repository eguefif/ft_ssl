#include "ft_ssl.h"

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

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

void round1op(u64, u64, u64, u64, u64, u64, u64);
void round2op(u64, u64, u64, u64, u64, u64, u64);
void round3Op(u64, u64, u64, u64, u64, u64, u64);
void round4Op(u64, u64, u64, u64, u64, u64, u64);
void round1(u32 *states, u32 *block);

void makeDigestFromPaddedTarget(char *digest, MD5Data *data) {
    assert(data->paddedTargetSize * 8 % 512 == 0);
    bzero(digest, 16);
    u32 states[4] = {0x01234567, 0x89abcdef, 0xfedcba98, 0x76543210};
    makeOutput(digest, states);
}

void makeOutput(char *digest, u32 *states) {
    for (u8 i = 0; i < 4; i++) {
        printf("\nstate: %x\n", states[i]);
        u16 lower = (u16)(states[i] & 0xFFFF);
        u16 higher = (u16)((states[i] & 0xFFFF0000) >> 16);
        *(u16 *)(digest + i * 4) = lower;
        *(u16 *)(digest + i * 4 + 2) = higher;
        printf("higher: %x lower: %x\n", higher, lower);
        printf("digest: %s\n", digest);
    }
}
