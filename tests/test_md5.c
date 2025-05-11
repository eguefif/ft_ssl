#include "../src/ft_ssl.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void testMd5(void) {
    char *target = "The quick brown fox jumps over the lazy dog";
    char *expected = "9e107d9d372bb6826bd81d3542a419d6";

    char *result = malloc(16);
    calculateMD5(result, target);
    CU_ASSERT(strncmp(result, target, 16) == 0);
    free(result);
}

// Test case took on https://www.geeksforgeeks.org/what-is-the-md5-algorithm/
void testGetPaddedTargetSize(void) {
    int result = getPaddedTargetSize(1000 / 8);
    CU_ASSERT(result == 1536 / 8);
}

void testPadTarget(void) {
    MD5Data data;

    u64 size = 1000 / 8;
    data.target = (char *)malloc(size + 1);
    data.targetSize = 1000 / 8;
    bzero(data.target, size + 1);
    for (u64 i = 0; i < size; i++) {
        data.target[i] = 'a';
    }
    data.paddedTargetSize = getPaddedTargetSize(strlen(data.target));
    char *buffer = (char *)malloc(data.paddedTargetSize);

    padTarget(&data);
    appendLength(&data);

    // Check if first padded bit is 1
    CU_ASSERT(data.target[size] == (char)128);

    // Check if the rest is 0 until length
    u64 counter = 0;
    for (int i = size + 1; i < (data.paddedTargetSize - 8); i++) {
        counter += (u64)data.target[i];
    }
    CU_ASSERT(counter == 0);

    // Check the length
    u64 length = *(u64 *)(data.target + data.paddedTargetSize - 8);
    CU_ASSERT(length == size);
}

void testMakeOutput(void) {
    char *digest = (char *)malloc(17);
    u32 states[4] = {0x31323334, 0x41424344, 0x45464748, 0x61626364};
    digest[16] = 0;
    makeOutput(digest, states);
    printf("\nresult %s\n", digest);
    CU_ASSERT(strncpy(digest, "4321DCBAHGFEdcba", 16) == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Test MD5", 0, 0);
    CU_add_test(suite, "Test of calculateMD5", testMd5);
    CU_add_test(suite, "Test of getTargetPaddedSize", testGetPaddedTargetSize);
    CU_add_test(suite, "Test of testPadTarget", testPadTarget);
    CU_add_test(suite, "Test of testMakeOutput", testMakeOutput);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
