#include "md5.h"
#include "ft_ssl.h"

void runMD5(Params params) { printf("Running MD5\n"); }

void calculateMD5(char *digest, char *target) {
    bzero(digest, 16);
    int size = getPaddedTargetSize(target);
    char *paddedTarget = (char *)malloc(size);
    padTarget(target, paddedTarget);

    free(paddedTarget);
}

int getPaddedTargetSize(char *target) { return strlen(target); }
void padTarget(char *target, char *paddedTarget) {}
