/*
 * File:   test_FileSystem_Close_correct.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 13:54:04
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <CUnit/Basic.h>
#include "../Windows\OSALInit.h"

/*
 * CUnit Test Suite
 */

static char addressP[OSAL_address_max_length];

int init_suite(void) {
    OSAL_APIInit();
    strcpy(addressP, addressD);
    strcat(addressP, OSAL_File_name);
    return 0;
}

int clean_suite(void) {
    DeleteFileA(addressP);
    return 0;
}

void testOSAL_Close_correct() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CU_ASSERT_EQUAL(OSAL_Close(File), OSAL_Test_PASS);
}

void testOSAL_Close_correct1() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CU_ASSERT_EQUAL(OSAL_Close(File), OSAL_Test_PASS);
}

void testOSAL_Close_correct2() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CU_ASSERT_EQUAL(OSAL_Close(File), OSAL_Test_PASS);
}

void testOSAL_Close_worse() {
    HANDLE File;
    int result = OSAL_Close(File);
    CU_ASSERT_EQUAL(OSAL_Close(File), OSAL_Test_FAIL);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Close", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Close_correct", testOSAL_Close_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Close_correct1", testOSAL_Close_correct1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Close_correct2", testOSAL_Close_correct2))||
        (NULL == CU_add_test(pSuite, "testOSAL_Close_worse", testOSAL_Close_worse))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}