/*
 * File:   test_OS_PrintfDIsable.c
 * Author: Luka Maletic
 *
 * Created on 14 Sep 2020, 13:33:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
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

void testOSAL_PrintfDisable() {
    OSAL_PrintfDisable();
    CU_ASSERT_EQUAL(OSAL_Printf(OSAL_Printf_string), OSAL_Test_FAIL);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_PrintfDIsable", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_PrintfDisable", testOSAL_PrintfDisable))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}