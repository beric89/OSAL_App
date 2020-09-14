/*
 * File:   test_FileSystem_Write.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 14:22:54
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <windows.h>
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

void testOSAL_Write_worse() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );

    CU_ASSERT_EQUAL(OSAL_Write(File, OSAL_Write_text), 0);
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Write_worse1() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    
    CU_ASSERT_EQUAL(OSAL_Write(File, ""), OSAL_Test_FAIL);
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Write_correct() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    
    CU_ASSERT_EQUAL(OSAL_Write(File, OSAL_Write_text), OSAL_Test_PASS);
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Write_correct1() {
    HANDLE File = CreateFile(
        addressP,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    
    CU_ASSERT_EQUAL(OSAL_Write(File, OSAL_Write_text), OSAL_Test_PASS);
    CloseHandle(File);
    DeleteFileA(addressP);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Write", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Write_worse", testOSAL_Write_worse))||
        (NULL == CU_add_test(pSuite, "testOSAL_Write_worse1", testOSAL_Write_worse1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Write_correct", testOSAL_Write_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Write_correct1", testOSAL_Write_correct))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}