#ifndef SHA256
#include "ft_ssl_types.h"

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
