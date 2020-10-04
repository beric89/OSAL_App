#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <windows.h>
#include "../Windows\OSALInit.h"
/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_GetLocalTime() {
    // TODO: pogledati komentar u clock.c
    int* localTime = OSAL_GetLocalTime();
    SYSTEMTIME t;
    GetLocalTime(&t);
    int pom[6];
    pom[0] = t.wYear;
    pom[1] = t.wMonth;
    pom[2] = t.wDay;
    pom[3] = t.wHour;
    pom[4] = t.wMinute;
    pom[5] = t.wSecond;
    pom[6] = t.wMilliseconds;
    for (int i = 0; i < 7; i++)
    {
        CU_ASSERT_EQUAL(pom[i], localTime[i]);
    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_GetLocalTime", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_GetLocalTime", testOSAL_GetLocalTime))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}