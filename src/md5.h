#ifndef MD5
#include "ft_ssl_types.h"

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

typedef struct {
    u32 states[4];
    u8 buffer[64];
    u64 bitsCount;
    u8 index;
} MD5Data;

MD5Data md5Init();
void md5Update(MD5Data *data, u8 *input, u64 inputLen);
void md5Finalize(MD5Data *data, u8 *digest);

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
#endif
