#ifndef FT_SSL
#include <stdio.h>
#include <string.h>
#define true 1
#define false 0
#define EXIT_FAILURE 1

typedef int boolean;

typedef struct {
    boolean p;
    boolean q;
    boolean r;
    boolean s;
} Flags;

typedef struct {
    char *command;
    Flags flags;
    char *file;
} Params;
#endif
