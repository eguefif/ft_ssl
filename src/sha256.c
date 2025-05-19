#include "sha256.h"
#include "ft_ssl.h"

const u32 K[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

void sha256Process(SHA256Context *ctx);
void initMessageSchedule(u32 *w, u32 *block);

void calculateSHA256(u8 *digest, u8 *target) {
    SHA256Context ctx = sha256Init();
    sha256Update(&ctx, target, strlen((char *)target));
    sha256Finalize(&ctx, digest);
}

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
    // u64 is in little-endian, we need to reverse the size to write
    // the size in big-endian in the padding
    length[1] = ctx->bitsCount & 0xFFFFFFFF;
    length[0] = (ctx->bitsCount >> 32) & 0xFFFFFFFF;
    u32ArrayToCharBE(&ctx->buffer[64 - 8], length, 2);
    sha256Process(ctx);
    u32ArrayToCharBE(digest, ctx->states, 8);
}

void sha256Process(SHA256Context *ctx) {
    u32 block[16];
    charToU32ArrayBE(block, ctx->buffer, 16);
    u32 w[64];
    initMessageSchedule(w, block);
    u32 a = ctx->states[0], b = ctx->states[1], c = ctx->states[2],
        d = ctx->states[3], e = ctx->states[4], f = ctx->states[5],
        g = ctx->states[6], h = ctx->states[7];

    u32 t1 = 0;
    u32 t2 = 0;
    for (int t = 0; t < 64; t++) {
        t1 = (h + BSIG1(e) + CH(e, f, g) + K[t] + w[t]) % MAX_U32;
        t2 = (BSIG0(a) + MAJ(a, b, c)) % MAX_U32;
        h = g;
        g = f;
        f = e;
        e = (d + t1) % MAX_U32;
        d = c;
        c = b;
        b = a;
        a = (t1 + t2) % MAX_U32;
    }

    ctx->states[0] = (ctx->states[0] + a) % MAX_U32;
    ctx->states[1] = (ctx->states[1] + b) % MAX_U32;
    ctx->states[2] = (ctx->states[2] + c) % MAX_U32;
    ctx->states[3] = (ctx->states[3] + d) % MAX_U32;
    ctx->states[4] = (ctx->states[4] + e) % MAX_U32;
    ctx->states[5] = (ctx->states[5] + f) % MAX_U32;
    ctx->states[6] = (ctx->states[6] + g) % MAX_U32;
    ctx->states[7] = (ctx->states[7] + h) % MAX_U32;
}

void initMessageSchedule(u32 *w, u32 *block) {
    for (int i = 0; i < 16; i++) {
        w[i] = block[i];
    }
    for (int i = 16; i < 64; i++) {
        w[i] = (SSIG1(w[i - 2]) + w[i - 7] + SSIG0(w[i - 15]) + w[i - 16]) %
               MAX_U32;
    }
}
