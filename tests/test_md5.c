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

// Test case took on https://www.geeksforgeeks.org/what-is-the-md5-algorithm/
void testGetPaddedTargetSize(void) {
    int result = getPaddedTargetSize(1000 / 8);
    CU_ASSERT(result == 1536 / 8);
}

void testPadTarget(void) {
    u64 size = 1000 / 8;
    char *target = (char *)malloc(size);
    for (int i = 0; i < size; i++) {
        target[i] = 'a';
    }
    u64 paddedTargetSize = getPaddedTargetSize(strlen(target));
    char *paddedTarget = (char *)malloc(paddedTargetSize);
    padTarget(target, paddedTarget, size);

    CU_ASSERT(paddedTarget[size] == (char)128);
    for (int i = size + 1; i < (paddedTargetSize - 8); i++) {
        CU_ASSERT(paddedTarget[size] == (char)0);
    }
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
