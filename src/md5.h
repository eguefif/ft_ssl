#ifndef MD5
#include "ft_ssl_types.h"

u64 getPaddedTargetSize(u64 sizeInByte);
void padTarget(char *target, char *paddedTarget, u64 size);
#endif
