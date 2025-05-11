#include "../src/ft_ssl.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void testMd5(void) {
    char *target = "The quick brown fox jumps over the lazy dog";
    char *expected = "9e107d9d372bb6826bd81d3542a419d6";

    char *result = malloc(16);
    calculateMD5(result, target);
    CU_ASSERT(strncmp(result, target, strlen(target)) == 0);
}

void testGetPaddedTargetSize(void) {
    char *target = "The quick";

    int result = getPaddedTargetSize(target);
    CU_ASSERT(result == 5);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test MD5", 0, 0);
    CU_add_test(suite, "Test of calculateMD5", testMd5);
    CU_add_test(suite, "Test of getTargetPaddedSize", testGetPaddedTargetSize);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
