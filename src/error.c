#include <stdio.h>

void printInvalidCommandError(char *command) {
    printf("ft_ssl: Error: %s is an invalid command\n\n", command);
    printf("Commands:\nmd5\nsha256\n\nFlags:\n-p -q -r -s\n");
}
