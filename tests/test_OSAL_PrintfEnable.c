/*
 * File:   test_OS_PrintfEnable.c
 * Author: Luka Maletic
 *
 * Created on 14 Sep 2020, 13:35:39
 */

#include "../OSALTestHeader.h"
/*
 * CUnit Test Suite
 */

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_PrintfEnable() {
    OSAL_PrintfEnable();
    CU_ASSERT_EQUAL(consoleEnabled, OSAL_CONSOLE_ENABLED);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_PrintfEnable", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_PrintfEnable", testOSAL_PrintfEnable))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}