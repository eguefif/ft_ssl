#ifndef SHA256
#include "ft_ssl_types.h"

#define ROTR(X, S) (((X) >> (S)) | ((X) << (32 - (S))))
#define ROTL(X, S) (((X) << (S)) | ((X) >> (32 - (S))))

#define CH(X, Y, Z) (((X) & (Y)) ^ ((~(X)) & (Z)))
#define MAJ(X, Y, Z) (((X) & (Y)) ^ ((X) & (Z)) ^ ((Y) & (Z)))
#define BSIG0(X) (ROTR(X, 2) ^ ROTR(X, 13) ^ ROTR(X, 22))
#define BSIG1(X) (ROTR(X, 6) ^ ROTR(X, 11) ^ ROTR(X, 25))
#define SSIG0(X) (ROTR(X, 7) ^ ROTR(X, 18) ^ ((X) >> 3))
#define SSIG1(X) (ROTR(X, 17) ^ ROTR(X, 19) ^ ((X) >> 10))
#define MAX_U32 ((u32)pow(2, 32))

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
