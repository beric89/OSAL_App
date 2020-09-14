/*
 * File:   test_OS_Remove.c
 * Author: Luka Maletic
 *
 * Created on 22 Sep 2020, 10:53:11
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
    return 0;
}

void testOSAL_Remove_worse() {
    char* name = "aaaaaaaaaaaaa";
    CU_ASSERT_EQUAL(OSAL_Remove(name), OSAL_Test_FAIL);
}

void testOSAL_Remove_worse1() {
    char* name = "";
    CU_ASSERT_EQUAL(OSAL_Remove(name),OSAL_Test_FAIL);
}

void testOSAL_Remove_worse2() {
    char* name = OSAL_File_name;
    CU_ASSERT_EQUAL(OSAL_Remove(name), OSAL_Test_FAIL);
}

void testOSAL_Remove_worse3() {
    char* name = OSAL_File_name;
    CU_ASSERT_EQUAL(OSAL_Remove(name), OSAL_Test_FAIL);
}

void testOSAL_Remove_correct() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CloseHandle(File);
    CU_ASSERT_EQUAL(OSAL_Remove(OSAL_File_name), OSAL_Test_PASS);
}

void testOSAL_Remove_correct1() {
    OSAL_APIInit();
    HANDLE File = CreateFile(
        addressP,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CloseHandle(File);
    CU_ASSERT_EQUAL(OSAL_Remove(OSAL_File_name), OSAL_Test_PASS);
}

void testOSAL_Remove_correct2() {
    OSAL_APIInit();
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CloseHandle(File);
    CU_ASSERT_EQUAL(OSAL_Remove(OSAL_File_name), OSAL_Test_PASS);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Remove", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Remove_worse", testOSAL_Remove_worse))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_worse1", testOSAL_Remove_worse1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_worse2", testOSAL_Remove_worse2))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_worse3", testOSAL_Remove_worse3))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_correct", testOSAL_Remove_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_correct1", testOSAL_Remove_correct1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_correct2", testOSAL_Remove_correct2))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}