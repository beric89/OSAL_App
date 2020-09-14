/*
 * File:   test_FileSystem_Open.c
 * Author: Luka Maletic
 *
 * Created on 22 Sep 2020, 16:01:06
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

void testOSAL_Open_worse() {
    char* name = OSAL_File_name;
    char* access = "w";
    int result = OSAL_Open(name, access);
    CU_ASSERT_PTR_NULL(result);
}

void testOSAL_Open_worse1() {
    char* name = "testaaaa.txt";
    char* access = "w";
    int result = OSAL_Open(name, access);
    CU_ASSERT_PTR_NULL(result);
}

void testOSAL_Open_worse2() {
    char* name = "";
    char* access = "w";
    int result = OSAL_Open(name, access);
    CU_ASSERT_PTR_NULL(result);
}

void testOSAL_Open_worse3() {
    char* name = OSAL_File_name;
    char* access = "";
    int result = OSAL_Open(name, access);
    CU_ASSERT_PTR_NULL(result);
}

void testOSAL_Open_correct() {
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
    
    File = OSAL_Open(OSAL_File_name, "r");
    CU_ASSERT_PTR_NOT_EQUAL(File, ERROR_FILE_NOT_FOUND);
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);
    CU_ASSERT_PTR_NOT_NULL(File);
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Open_correct1() {
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
    
    File = OSAL_Open(OSAL_File_name, "r");
    CU_ASSERT_PTR_NOT_EQUAL(File, ERROR_FILE_NOT_FOUND);
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);
    CU_ASSERT_PTR_NOT_NULL(File);
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Open_correct2() {
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
    
    File = OSAL_Open(OSAL_File_name, "r");
    CU_ASSERT_PTR_NOT_EQUAL(File, ERROR_FILE_NOT_FOUND);
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);
    CU_ASSERT_PTR_NOT_NULL(File);
    CloseHandle(File);
    DeleteFileA(addressP);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Open", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Open_worse", testOSAL_Open_worse))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_worse1", testOSAL_Open_worse1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_worse2", testOSAL_Open_worse2))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_worse3", testOSAL_Open_worse3))||    
        (NULL == CU_add_test(pSuite, "testOSAL_Open_correct", testOSAL_Open_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_correct1", testOSAL_Open_correct1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_correct2", testOSAL_Open_correct2))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}