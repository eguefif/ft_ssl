#include "md5.h"
#include "ft_ssl.h"

void runMD5(Params params) { printf("Running MD5\n"); }
void makeDigest(char *digest, char *paddedTarget);

void calculateMD5(char *digest, char *target) {
    bzero(digest, 16);
    u64 size = getPaddedTargetSize(strlen(target));
    char *paddedTarget = (char *)malloc(size);
    padTarget(target, paddedTarget, size);
    makeDigest(digest, paddedTarget);
    free(paddedTarget);
}

u64 getPaddedTargetSize(u64 sizeInByte) {
    u64 retval = 0;
    u64 targetSize = sizeInByte * 8;
    i64 rest = targetSize % 512;
    i64 quotient = targetSize / 512;

    if ((512 - rest) < 64) {
        retval = (quotient + 1 + 1) * 512;
    } else {
        retval = (quotient + 1) * 512;
    }
    retval /= 8;
    return retval;
}

void padTarget(char *target, char *paddedTarget, u64 paddedTargetSize) {
    u64 sizeInByte = strlen(target);
    assert(paddedTargetSize - sizeInByte >= 64);

    bzero(paddedTarget, paddedTargetSize);

    strncpy(target, paddedTarget, sizeInByte);

    if (paddedTargetSize > (sizeInByte + 65)) {
        paddedTarget[sizeInByte] = 0b10000000;
        *(u64 *)(paddedTarget + paddedTargetSize - 8) = sizeInByte;
    } else {
        *(u64 *)(paddedTarget + paddedTargetSize - 8) = sizeInByte;
    }
}

void makeDigest(char *digest, char *paddedTarget) {
    assert(strlen(paddedTarget) * 8 % 512 == 0);
}
