#include "ft_ssl.h"
#define MINIMUM_PADDING_SIZE 64 + 1

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
    u64 paddedTargetSizeInBit = 0;
    u64 targetSizeInBit = sizeInByte * 8;
    i64 rest = targetSizeInBit % 512;
    i64 quotient = targetSizeInBit / 512;

    if ((512 - rest) < MINIMUM_PADDING_SIZE) {
        paddedTargetSizeInBit = (quotient + 1 + 1) * 512;
    } else {
        paddedTargetSizeInBit = (quotient + 1) * 512;
    }
    return paddedTargetSizeInBit / 8;
}

void padTarget(MD5Data *data) {
    assert(data->paddedTargetSize - data->targetSize >= 8);

    bzero(data->paddedTarget, data->paddedTargetSize);
    strncpy(data->paddedTarget, data->target, data->targetSize);
    data->paddedTarget[data->targetSize] = 0b10000000;
    appendTargetSize(data);
}

void appendTargetSize(MD5Data *data) {
    u64 length = data->targetSize % (u64)pow(2, 64);
    *(u64 *)(data->paddedTarget + data->paddedTargetSize - 8) =
        data->targetSize;
}

void makeDigestFromPaddedTarget(char *digest, MD5Data *data) {
    assert(data->paddedTargetSize * 8 % 512 == 0);
    bzero(digest, 16);
}
