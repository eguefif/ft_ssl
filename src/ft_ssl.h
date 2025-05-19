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
#ifndef TARGET_MAX_SIZE
#define TARGET_MAX_SIZE 50000
#endif

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
void calculateSHA256(u8 *digest, u8 *target);

void getTarget(u8 *content, char *target);

void u64ToChar(u8 *output, u64 input);
void u32ArrayToChar(u8 *output, u32 *input, u64 len);
void charToU32Array(u32 *output, u8 *input, u64 len);

void charToU32ArrayBE(u32 *output, u8 *input, u64 len);
void u32ArrayToCharBE(u8 *output, u32 *input, u64 len);
#endif
