#include "ft_ssl.h"
#define MINIMUM_PADDING_SIZE 64 + 1

void makeDigestFromPaddedTarget(char *digest, MD5Data *data);
void padTarget(MD5Data *data);
void pad(MD5Data *data);

void runMD5(Params params) { printf("Running MD5\n"); }

void calculateMD5(char *digest, char *target) {
    MD5Data data;

    data.target = target;
    padTarget(&data);
    appendLength(&data);
    makeDigestFromPaddedTarget(digest, &data);
    free(data.target);
}

void padTarget(MD5Data *data) {
    data->targetSize = strlen(data->target);
    u64 paddedTargetSize = getPaddedTargetSize(data->targetSize);
    char *buffer = (char *)malloc(paddedTargetSize);

    assert(paddedTargetSize - data->targetSize >= 8);

    bzero(buffer, paddedTargetSize);
    strncpy(buffer, data->target, data->targetSize);
    buffer[data->targetSize] = 0b10000000;
    data->paddedTargetSize = paddedTargetSize;
    data->target = buffer;
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

void appendLength(MD5Data *data) {
    u64 length = data->targetSize % (u64)pow(2, 64);
    *(u64 *)(data->target + data->paddedTargetSize - 8) = length;
}

void makeDigestFromPaddedTarget(char *digest, MD5Data *data) {
    assert(data->paddedTargetSize * 8 % 512 == 0);
    bzero(digest, 16);
}
