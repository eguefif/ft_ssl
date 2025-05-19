#include "ft_ssl.h"

Params parseParams(i64 argc, char **argv) {
    Params params;

    memset(&params, 0, sizeof(Params));

    params.command = getCommand(argv[1]);
    params.commandValue = argv[1];
    if (argc > 2) {
        for (i64 i = 2; i < argc; i++) {
            if (argv[i] == 0) {
                break;
            }
            if (argv[i][0] == '-') {
                parseFlags(argv[i], &(params.flags));
            } else {
                u64 argvLen = strlen(argv[i]);
                u64 len =
                    argvLen < MAX_FILENAME_SIZE ? argvLen : MAX_FILENAME_SIZE;
                memcpy(params.target, argv[i], len);
            }
        }
    }
    if (params.target[0] == 0) {
        memcpy(params.target, "stdin", 5);
    }
    return params;
}

void parseFlags(char *arg, Flags *flags) {
    u64 size = strlen(arg);

    for (u64 i = 1; i < size; i++) {
        switch (arg[i]) {
        case 'p':
            flags->p = true;
            break;
        case 'q':
            flags->q = true;
            break;
        case 'r':
            flags->r = true;
            break;
        case 's':
            flags->s = true;
            break;
        }
    }
}

i64 getCommand(char *command) {
    if (!strncmp("md5", command, 3)) {
        return MD5;
    } else if (!strncmp("sha256", command, 5)) {
        return SHA256;
    }
    return -1;
}
