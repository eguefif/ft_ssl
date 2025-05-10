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

int runSsl(Params params) {
    switch (params.command) {
    case MD5:
        runMD5(params);
        break;
    case SHA256:
        runSHA256(params);
        break;
    default:
        printInvalidCommandError(params.commandValue);
        break;
    }
    return 0;
}
