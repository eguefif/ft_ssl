#include "sha256.h"
#include "ft_ssl.h"

void sha256Process(SHA256Context *ctx);

void calculateSHA256(u8 *digest, u8 *target) {}

SHA256Context sha256Init() {
    SHA256Context ctx;

    memset(&ctx, 0, sizeof(SHA256Context));

    ctx.states[0] = 0x6a09e667;
    ctx.states[1] = 0xbb67ae85;
    ctx.states[2] = 0x3c6ef372;
    ctx.states[3] = 0xa54ff53a;
    ctx.states[4] = 0x510e527f;
    ctx.states[5] = 0x9b05688c;
    ctx.states[6] = 0x1f83d9ab;
    ctx.states[7] = 0x5be0cd19;

    return ctx;
}

void sha256Update(SHA256Context *ctx, u8 *input, u64 inputLen) {
    u64 i = 0;

    ctx->bitsCount += inputLen * 8;
    if (inputLen >= 64) {
        for (i = 0; i <= (inputLen - 64); i += 64) {
            memcpy((char *)ctx->buffer, (char *)&input[i], 64);
            sha256Process(ctx);
        }
    } else
        i = 0;

    ctx->index = inputLen - i;
    strncpy((char *)ctx->buffer, (char *)&input[i], inputLen - i);
}

void sha256Finalize(SHA256Context *ctx, u8 *digest) {
    if (ctx->index < 56) {
        memset(&ctx->buffer[ctx->index], 0, 64 - ctx->index);
        ctx->buffer[ctx->index] = 0x80;
    } else {
        ctx->buffer[ctx->index] = 0x80;
        sha256Process(ctx);
        memset(ctx->buffer, 0, 64);
    }
    u32 length[2];
    length[0] = ctx->bitsCount & 0xFFFFFFFF;
    length[1] = (ctx->bitsCount >> 32) & 0xFFFFFFFF;
    u32ArrayToChar(&ctx->buffer[64 - 8], length, 2);
    sha256Process(ctx);
    u32ArrayToChar(digest, ctx->states, 8);
}

void sha256Process(SHA256Context *ctx) {}
