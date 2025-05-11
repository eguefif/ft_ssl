#include "ft_ssl.h"

u32 F(u32 X, u32 Y, u32 Z);
u32 G(u32 X, u32 Y, u32 Z);
u32 H(u32 X, u32 Y, u32 Z);
u32 I(u32 X, u32 Y, u32 Z);

void makeDigestFromPaddedTarget(char *digest, MD5Data *data) {
    assert(data->paddedTargetSize * 8 % 512 == 0);
    bzero(digest, 16);
    u32 A = 0x01234567;
    u32 B = 0x89abcdef;
    u32 C = 0xfedcba98;
    u32 D = 0x76543210;
}

u32 F(u32 X, u32 Y, u32 Z) { return X & Y | (!X) & Z; }
u32 G(u32 X, u32 Y, u32 Z) { return X & Z | Y & (!Z); }
u32 H(u32 X, u32 Y, u32 Z) { return X ^ Y ^ Z; }
u32 I(u32 X, u32 Y, u32 Z) { return Y ^ (X | (!Z)); }
