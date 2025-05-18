#include "../src/ft_ssl.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void printDigest(unsigned char *digest) {
    for (int i = 0; i < 16; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");
}

void testMd5(void) {
    char *target = "The quick brown fox jumps over the lazy dog";
    char *expected = "9e107d9d372bb6826bd81d3542a419d6";

    char *result = malloc(33);
    result[32] = 0;
    calculateMD5((u8 *)result, (u8 *)target);
    printf("result  : %s\n", result);
    printf("expected: %s\n", expected);
    CU_ASSERT(strncmp(result, target, 32) == 0);
    free(result);
}

void testMd5EmptyTarget(void) {
    char *target = "";
    char *expected = "d41d8cd98f00b204e9800998ecf8427e";

    u8 result[17];
    result[16] = 0;
    calculateMD5(result, (u8 *)target);
    printf("\nresult  : ");
    printDigest(result);
    printf("expected: %s\n", expected);
    CU_ASSERT(strncmp((char *)result, target, 32) == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test MD5", 0, 0);
    // CU_add_test(suite, "Test of calculateMD5", testMd5);
    CU_add_test(suite, "Test of calculateMD5: empty target",
                testMd5EmptyTarget);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
