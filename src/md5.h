#ifndef MD5
#include "ft_ssl_types.h"

typedef struct {
    char *target;
    u64 targetSize;
    u64 paddedTargetSize;
} MD5Data;

u64 getPaddedTargetSize(u64 sizeInByte);
void padTarget(MD5Data *data);
void appendLength(MD5Data *data);
void makeDigestFromPaddedTarget(char *digest, MD5Data *data);
#endif
