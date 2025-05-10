#ifndef FT_SSL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1
#define false 0
#define EXIT_FAILURE 1

#define MD5 0
#define SHA256 1

typedef int boolean;

typedef struct {
    boolean p;
    boolean q;
    boolean r;
    boolean s;
} Flags;

typedef struct {
    int command;
    char *commandValue;
    Flags flags;
    char *file;
} Params;

int runSsl(Params);

Params parseParams(int, char **);
void parseFlags(char *, Flags *);
int getCommand(char *);

void printInvalidCommandError(char *command);

void runMD5(Params params);

void calculateMD5(char *digest, char *target);
void runSHA256(Params params);

#endif
