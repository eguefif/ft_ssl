#include "ft_ssl.h"

void runMD5(Params params) { printf("Running MD5\n"); }

void calculateMD5(u8 *digest, u8 *target) {
    MD5Data data = md5Init();
    md5Update(&data, target, strlen(target));
    md5Finalize(&data, digest);
}
