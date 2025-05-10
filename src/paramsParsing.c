#include "ft_ssl.h"

Params parseParams(int argc, char **argv) {
    Params params;

    bzero(&params, sizeof(Params));

    params.command = getCommand(argv[1]);
    params.commandValue = argv[1];
    if (argc > 2) {

        for (int i = 0; i < argc; i++) {
            if (argv[i] == 0) {
                break;
            }
            if (argv[i][0] == '-') {
                parseFlags(argv[i], &(params.flags));
            } else {
                params.file = argv[i];
            }
        }
    }
    return params;
}

void parseFlags(char *arg, Flags *flags) {
    int size = strlen(arg);

    for (int i = 1; i < size; i++) {
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

int getCommand(char *command) {
    if (!strncmp("md5", command, 3)) {
        return MD5;
    } else if (!strncmp("sha256", command, 5)) {
        return SHA256;
    }
    return -1;
}
