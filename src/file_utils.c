#include "ft_ssl.h"
#include <fcntl.h>

void getStdin(u8 *target, u64 max) {
    int n = read(0, target, (size_t)(max - 1));
    target[n] = 0;
}

void getFile(u8 *target, char *filename, u64 max) {
    int fd = open(filename, O_RDONLY, 0);
    int n = read(fd, target, (size_t)(max - 1));
    target[n] = 0;
}

void getContent(u8 *target, char *param, u64 max) {
    u64 contentSize = strlen(param);
    u64 len = contentSize < max ? contentSize : max;
    memcpy(target, param, len);
}
