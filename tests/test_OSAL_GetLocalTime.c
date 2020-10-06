/*
 * CUnit Test Suite
 */

#include "../OSALTestHeader.h"
int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_GetLocalTime() {
    OSAL_TimeType localTime = OSAL_GetLocalTime();
    SYSTEMTIME t;
    GetLocalTime(&t);
    CU_ASSERT_EQUAL(t.wYear, localTime.year);
    CU_ASSERT_EQUAL(t.wMonth, localTime.month);
    CU_ASSERT_EQUAL(t.wDay, localTime.day);
    CU_ASSERT_EQUAL(t.wHour, localTime.hour);
    CU_ASSERT_EQUAL(t.wMinute, localTime.minute);
    CU_ASSERT_EQUAL(t.wSecond, localTime.second);
    CU_ASSERT_EQUAL(t.wMilliseconds, localTime.milliseconds);
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