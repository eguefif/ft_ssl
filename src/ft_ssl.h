#ifndef FT_SSL
#include "ft_ssl_types.h"
#include "md5.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT_FAILURE 1

#define MD5 0
#define SHA256 1

i64 runSsl(Params);

Params parseParams(i64, char **);
void parseFlags(char *, Flags *);
i64 getCommand(char *);

void printInvalidCommandError(char *command);

void runMD5(Params params);

void calculateMD5(char *digest, char *target);
void runSHA256(Params params);
#endif
