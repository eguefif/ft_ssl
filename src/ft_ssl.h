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

#define MD5 0
#define SHA256 1

i64 runSsl(Params);

Params parseParams(i64, char **);
void parseFlags(char *, Flags *);
i64 getCommand(char *);

void printInvalidCommandError(char *command);

void runMD5(Params params);

void calculateMD5(u8 *digest, u8 *target);
void runSHA256(Params params);

// File stdin utilities
void getStdin(u8 *target, u64 max);
void getContent(u8 *target, char *param, u64 max);
void getFile(u8 *target, char *filename, u64 max);
#endif
