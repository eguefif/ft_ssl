#include "../src/ft_ssl.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void printDigest(unsigned char *digest) {
    for (int i = 0; i < 16; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

void toHexDigest(char *hexdigest, unsigned char *digest) {
    for (int i = 0; i < 16; i++) {
        sprintf(&hexdigest[i * 2], "%02x", digest[i]);
    }
}
void testMd5GreaterThan64(void) {
    char *target =
        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean.";
    char *expected = "f1e06497576d815fc8939fada933a6b3";

    u8 result[16];
    calculateMD5(result, (u8 *)target);

    char hexdigest[32];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 32) == 0);
}

void testMd5NotEnoughForPadding(void) {
    char *target = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit.";
    char *expected = "a84e9dae73341f1e9764f349701a5adf";

    u8 result[16];
    calculateMD5(result, (u8 *)target);

    char hexdigest[32];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 32) == 0);
}

void testMd5HelloWorld(void) {
    char *target = "Hello, world!";
    char *expected = "6cd3556deb0da54bca060b4c39479839";

    u8 result[16];
    calculateMD5(result, (u8 *)target);

    char hexdigest[32];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 32) == 0);
}

void testMd5EmptyTarget(void) {
    char *target = "";
    char *expected = "d41d8cd98f00b204e9800998ecf8427e";

    u8 result[16];
    calculateMD5(result, (u8 *)target);
    char hexdigest[32];
    toHexDigest(hexdigest, result);
    CU_ASSERT(strncmp(hexdigest, expected, 32) == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test MD5", 0, 0);
    CU_add_test(suite, "Test of calculateMD5", testMd5HelloWorld);
    CU_add_test(suite, "Test of calculateMD5: empty target",
                testMd5EmptyTarget);
    CU_add_test(suite, "Test of when not enough for padding",
                testMd5NotEnoughForPadding);

    CU_add_test(suite, "Test of when target greater than 64",
                testMd5GreaterThan64);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
