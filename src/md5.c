#include "ft_ssl.h"

void makeDigestFromPaddedTarget(char *digest, MD5Data *data);
void appendTargetSize(MD5Data *data);
void initPaddedTarget(MD5Data *data, char *target);

void runMD5(Params params) { printf("Running MD5\n"); }

void calculateMD5(char *digest, char *target) {
    MD5Data data;

    data.target = target;
    initPaddedTarget(&data, target);
    makeDigestFromPaddedTarget(digest, &data);
    free(data.paddedTarget);
}

void initPaddedTarget(MD5Data *data, char *target) {
    data->targetSize = strlen(target);
    data->paddedTargetSize = getPaddedTargetSize(data->targetSize);
    data->paddedTarget = (char *)malloc(data->paddedTargetSize);
    padTarget(data);
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

void padTarget(MD5Data *data) {
    assert(data->paddedTargetSize - data->targetSize >= 8);

    bzero(data->paddedTarget, data->paddedTargetSize);
    strncpy(data->paddedTarget, data->target, data->targetSize);
#include <unistd.h>
    write(1, &"test\n", 5);

    appendTargetSize(data);
}

void appendTargetSize(MD5Data *data) {
    if (data->paddedTargetSize >= (data->targetSize + 65)) {
        data->paddedTarget[data->targetSize] = 0b10000000;
        *(u64 *)(data->paddedTarget + data->paddedTargetSize - 8) =
            data->targetSize;
    } else {
        *(u64 *)(data->paddedTarget + data->paddedTargetSize - 8) =
            data->targetSize;
    }
}

void makeDigestFromPaddedTarget(char *digest, MD5Data *data) {
    assert(data->paddedTargetSize * 8 % 512 == 0);
    bzero(digest, 16);
}
