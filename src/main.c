#include "ft_ssl.h"

Params parseParams(int, char **);
void parseFlags(char *, Flags *);
void runSsl(Params);

int main(int argc, char **argv) {
    if (argc <= 1 || argc > 7) {
        printf("usage: ft_ssl command [flag] [file/string]\n");
    } else {
        Params params = parseParams(argc, argv);
        runSsl(params);
    }
    return 0;
}

Params parseParams(int argc, char **argv) {
    Params params;

    bzero(&params, sizeof(Params));

    params.command = argv[1];
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

void runSsl(Params params) {
    printf("Command: %s, file: %s\n", params.command, params.file);
    printf("Flags q: %d, p: %d, r: %d, s: %d\n", params.flags.q, params.flags.p,
           params.flags.r, params.flags.s);
}
