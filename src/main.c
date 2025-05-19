#include "ft_ssl.h"

int main(int argc, char **argv) {
    if (argc <= 1 || argc > 7) {
        printf("usage: ft_ssl command [flag] [file/string]\n");
    } else {
        Params params = parseParams(argc, argv);
        return runSsl(params);
    }
    return 0;
}

i64 runSsl(Params params) {
    switch (params.command) {
    case MD5:
    case SHA256:
        runHash(params);
        break;
    default:
        printInvalidCommandError(params.commandValue);
        break;
    }
    return 0;
}

void printHash(u8 *digest, u64 len) {
    for (u64 i = 0; i < len; i++) {
        printf("%02x", digest[i]);
    }
}

void runHash(Params params) {
    u8 target[TARGET_MAX_SIZE];
    u64 hashSize = 0;
    void (*hashFunction)(u8 *, u8 *) = 0;
    switch (params.command) {
    case MD5:
        hashSize = 16;
        hashFunction = &calculateMD5;
        printf("MD5");
        break;
    case SHA256:
        hashSize = 32;
        hashFunction = &calculateSHA256;
        printf("SHA256");
        break;
    }
    getTarget(target, params.target);
    if (params.flags.p) {
        printf("(\"%s\") ", target);
    }
    u8 digest[hashSize];
    hashFunction(digest, target);
    printHash(digest, hashSize);
    printf("\n");
}
