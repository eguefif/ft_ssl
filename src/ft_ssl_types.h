#ifndef FT_SSL_TYPE
#include <stdint.h>
#define true 1
#define false 0

typedef uint8_t boolean;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef struct {
    boolean p;
    boolean q;
    boolean r;
    boolean s;
} Flags;

typedef struct {
    i64 command;
    char *commandValue;
    Flags flags;
    char *file;
} Params;

#endif
