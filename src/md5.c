#include "md5.h"
#include "ft_ssl.h"

void appendLength(u64 sizeInByte, char *paddedTarget);
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

void padTarget(char *target, char *paddedTarget, u64 totalSize) {
    u64 sizeInByte = strlen(target);
    u64 sizeInBit = strlen(target) * 8;

    bzero(paddedTarget, totalSize);
    strncpy(target, paddedTarget, sizeInByte);

    paddedTarget[sizeInByte] = 0b10000000;
    appendLength(sizeInByte, paddedTarget);
}

void appendLength(u64 sizeInByte, char *paddedTarget) {}

void makeDigest(char *digest, char *paddedTarget) {
    assert(strlen(paddedTarget) * 8 % 512 == 0);
}
