#ifndef FT_SSL
#include "ft_ssl_types.h"
#include "md5.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define EXIT_FAILURE 1
#define TARGET_MAX_SIZE 5000

#define MD5 0
#define SHA256 1

i64 runSsl(Params);
void runHash(Params params);

Params parseParams(i64, char **);
void parseFlags(char *, Flags *);
i64 getCommand(char *);

void printInvalidCommandError(char *command);

void runMD5(Params params);

void calculateMD5(u8 *digest, u8 *target);
void runSHA256(Params params);

void getTarget(u8 *content, char *target);
#endif
