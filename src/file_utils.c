#include "ft_ssl.h"
#include <fcntl.h>

void getStdin(u8 *target) {
    int n = read(0, target, (size_t)(TARGET_MAX_SIZE - 1));
    target[n] = 0;
}

void getFile(u8 *target, char *filename) {
    int fd = open(filename, O_RDONLY, 0);
    int n = read(fd, target, (size_t)(TARGET_MAX_SIZE - 1));
    target[n] = 0;
}

void getParamContent(u8 *target, char *param) {
    u64 contentSize = strlen(param);
    u64 len = contentSize < TARGET_MAX_SIZE ? contentSize : TARGET_MAX_SIZE;
    memcpy(target, param, len);
}

void getTarget(u8 *content, char *target) {
    if (strncmp(target, "stdin", 5) == 0) {
        getStdin(content);
    } else {
        if (access(target, F_OK) == 0) {
            getFile(content, target);
        } else {
            getParamContent(content, target);
        }
    }
}
