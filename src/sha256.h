#ifndef SHA256
#include "ft_ssl_types.h"

#define ROTR(X, S) (((X) >> S) | ((X) << (32 - S)))
#define ROTL(X, S) (((X) << S) | ((X) >> (32 - S)))

#define CH(X, Y, Z) (((X) & ((Y)) ^ ((~X) & (Z)))
#define MAJ(X, Y, Z) (((X) & (Y)) ^ ((X) & (Z)) ^ ((Y) & (Z)))
#define BSIG0(X) (ROTR(X, 2) ^ ROTR(x, 13) ^ ROTR(X, 22))
#define BSIG1(X) (ROTR(X, 6) ^ ROTR(x, 11) ^ ROTR(X, 25))
#define SSIG0(X) (ROTR(X, 7) ^ ROTR(x, 18) ^ (X >> 3))
#define SSIG1(X) (ROTR(X, 17) ^ ROTR(x, 19) ^ (X >> 10))

typedef struct {
    u32 states[8];
    u8 buffer[64];
    u64 bitsCount;
    u8 index;
} SHA256Context;

SHA256Context sha256Init();
void sha256Update(SHA256Context *ctx, u8 *input, u64 inputLen);
void sha256Finalize(SHA256Context *ctx, u8 *digest);
#endif
