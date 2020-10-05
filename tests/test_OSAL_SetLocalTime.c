/*
 * File:   test_OS_SetLocalTime.c
 * Author: Luka Maletic
 *
 * Created on 15 Sep 2020, 11:32:22
 */

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

// TODO: pogledati komentar u clock.c
void testOSAL_SetLocalTime() {
    static int date[6];
    date[0] = 2020;
    date[1] = 9;
    date[2] = 14;
    date[3] = 13;
    date[4] = 30;
    date[5] = 29;
    date[6] = 421;
    
    OSAL_SetLocalTime(date);
    
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
        CU_ASSERT_EQUAL(date[i], pom[i]);
    }
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_SetLocalTime", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_SetLocalTime", testOSAL_SetLocalTime))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}