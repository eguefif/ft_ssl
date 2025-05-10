#include "ft_ssl.h"

void runMD5(Params params) { printf("Running MD5\n"); }

void calculateMD5(char *digest, char *target) {
    bzero(digest, 16);
    strncpy(digest, target, 16);
}
