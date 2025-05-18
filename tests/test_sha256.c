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
    char *expected = "2172f297164df75abb9c2d71b1003350";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}
void testSHA256GreaterThan64(void) {
    char *target =
        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean.";
    char *expected = "f1e06497576d815fc8939fada933a6b3";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

void testSHA256NotEnoughForPadding(void) {
    char *target = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit.";
    char *expected = "a84e9dae73341f1e9764f349701a5adf";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

void testSHA256HelloWorld(void) {
    char *target = "Hello, world!";
    char *expected = "6cd3556deb0da54bca060b4c39479839";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);

    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

void testSHA256EmptyTarget(void) {
    char *target = "";
    char *expected = "d41d8cd98f00b204e9800998ecf8427e";

    u8 result[32];
    calculateSHA256(result, (u8 *)target);
    char hexdigest[64];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 64) == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test SHA256", 0, 0);
    // CU_add_test(suite, "Test of calculateSHA256", testSHA256HelloWorld);
    CU_add_test(suite, "Test of calculateSHA256: empty target",
                testSHA256EmptyTarget);
    // CU_add_test(suite, "Test of when not enough for padding",
    //           testSHA256NotEnoughForPadding);

    // CU_add_test(suite, "Test of when target greater than 64",
    //          testSHA256GreaterThan64);
    // CU_add_test(suite, "Test of when target exactly 64",
    // testSHA256Exactly64);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
