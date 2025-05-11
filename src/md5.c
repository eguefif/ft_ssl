#include "md5.h"
#include "ft_ssl.h"

void runMD5(Params params) { printf("Running MD5\n"); }

void calculateMD5(char *digest, char *target) {
    bzero(digest, 16);
    int size = getPaddedTargetSize(strlen(target));
    char *paddedTarget = (char *)malloc(size);
    padTarget(target, paddedTarget);

    free(paddedTarget);
}

int getPaddedTargetSize(int sizeInByte) {
    int retval = 0;
    int targetSize = sizeInByte * 8;
    int rest = targetSize % 512;
    int quotient = targetSize / 512;

    if ((512 - rest) < 64) {
        retval = (quotient + 1 + 1) * 512;
    } else {
        retval = (quotient + 1) * 512;
    }
    retval /= 8;
    return retval;
}

void padTarget(char *target, char *paddedTarget) {}
