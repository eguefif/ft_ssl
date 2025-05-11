#ifndef MD5

#include "ft_ssl_types.h"

typedef struct {
    char *paddedTarget;
    u64 paddedTargetSize;
    char *target;
    u64 targetSize;
} MD5Data;

u64 getPaddedTargetSize(u64 sizeInByte);
void padTarget(MD5Data *data);
#endif
