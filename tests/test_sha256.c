#include "../src/ft_ssl.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void printDigest(unsigned char *digest) {
    for (int i = 0; i < 64; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

void toHexDigest(char *hexdigest, unsigned char *digest) {
    for (int i = 0; i < 32; i++) {
        sprintf(&hexdigest[i * 2], "%02x", digest[i]);
    }
}
void testSHA256Exactly64(void) {
    char *target =
        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean";
    char *expected =
        "8da1076d9d8c97918b2bbe3dfbf2b2d7f6cde56df323db5f91957c9f1d64aaa7";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}
void testSHA256GreaterThan64(void) {
    char *target =
        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean.";
    char *expected =
        "2c2727916d6d8f1152ad92ca6df246fff93103cbd4c029c07d9a552a373b0c20";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

void testSHA256NotEnoughForPadding(void) {
    char *target = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit.";
    char *expected =
        "1d32dc481e105799b079b5a1b18c2e302bc43bc5feac01450c7ffa50a1c65b92";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

void testSHA256HelloWorld(void) {
    char *target = "Hello, world";
    char *expected =
        "4ae7c3b6ac0beff671efa8cf57386151c06e58ca53a78d83f36107316cec125f";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);

    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

void testSHA256EmptyTarget(void) {
    char *target = "";
    char *expected =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);
    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test SHA256", 0, 0);
    CU_add_test(suite, "Test of calculateSHA256", testSHA256HelloWorld);
    CU_add_test(suite, "Test of calculateSHA256: empty target",
                testSHA256EmptyTarget);
    CU_add_test(suite, "Test of when not enough for padding",
                testSHA256NotEnoughForPadding);

    CU_add_test(suite, "Test of when target greater than 64",
                testSHA256GreaterThan64);
    CU_add_test(suite, "Test of when target exactly 64", testSHA256Exactly64);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
