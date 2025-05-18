#include "ft_ssl.h"

void getStdin(u8 *target, u64 max) {
    int n = read(0, target, (size_t)(max - 1));
    target[n] = 0;
}
