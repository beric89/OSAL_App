/*
 * File:   test_OS_Creeate.c
 * Author: Luka Maletic
 *
 * Created on 21 Sep 2020, 09:34:52
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

void testName_validation_worseLong() {
    char* name, *access;
    name = "aaaaaaaaaaa";
    access = "r";
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(result);
    CloseHandle(result);
}

void testName_validation_worseShort() {
    char* name, *access;
    name = "";
    access = "r";
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(result);
    CloseHandle(result);
}

void testAccess_validation_worse() {
    char* access,* name;
    access = "";
    name = OSAL_File_name;
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(result);
    CloseHandle(result);
}

void testAccess_validation_worse1() {
    char* access,* name;
    access = "aa";
    name = OSAL_File_name;
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(result);
    CloseHandle(result);
}

void testAccess_validation_correct() {
    char* access,* name;
    access = "r";
    name = OSAL_File_name;
    HANDLE* result = OSAL_Create(name,access);
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    DeleteFileA(addressP);
}

void testAccess_validation_correct1() {
    char* access,* name;
    access = "w";
    name = OSAL_File_name;
    HANDLE* result = OSAL_Create(name,access);
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    DeleteFileA(addressP);
}

void testAccess_validation_correct2() {
    char* access,* name;
    access = "r/w";
    name = OSAL_File_name;
    HANDLE* result = OSAL_Create(name,access);
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    DeleteFileA(addressP);
}

void testOSAL_Creat_correct() {
    char* name = OSAL_File_name;
    char* access = "r";
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    DeleteFileA(addressP);
}

void testOSAL_Creat_correct1() {
    char* name = OSAL_File_name;
    char* access = "w";
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    DeleteFileA(addressP);
}

void testOSAL_Creat_correct2() {
    char* name = OSAL_File_name;
    char* access = "r/w";
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    DeleteFileA(addressP);
}

void testOSAL_Creat_worse() {
    char* name = OSAL_File_name;
    char* access = "aa";
    HANDLE* result = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(result);
    DeleteFileA(addressP);
}

void testOSAL_Creat_duplicate() {
    char* name = OSAL_File_name;
    char* access = "r";
    HANDLE* result = OSAL_Create(name, access);
    
    char* name1 = OSAL_File_name;
    char* access1 = "r";
    HANDLE* result1 = OSAL_Create(name1, access1);
    CU_ASSERT_PTR_NULL(result1);        
    CU_ASSERT_PTR_NOT_NULL(result);
    CloseHandle(result);
    CloseHandle(result1);
    DeleteFileA(addressP);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Create", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testName_validation_worseShort", testName_validation_worseShort))||
        (NULL == CU_add_test(pSuite, "testName_validation_worseLong", testName_validation_worseLong))||
        (NULL == CU_add_test(pSuite, "testAccess_validation_worse", testAccess_validation_worse))||
        (NULL == CU_add_test(pSuite, "testAccess_validation_worse1", testAccess_validation_worse1)) ||
        (NULL == CU_add_test(pSuite, "testAccess_validation_correct", testAccess_validation_correct))||
        (NULL == CU_add_test(pSuite, "testAccess_validation_correct1", testAccess_validation_correct1))||
        (NULL == CU_add_test(pSuite, "testAccess_validation_correct2", testAccess_validation_correct2))||
        (NULL == CU_add_test(pSuite, "testOSAL_Creat_correct", testOSAL_Creat_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Creat_correct1", testOSAL_Creat_correct1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Creat_correct2", testOSAL_Creat_correct2)) ||
        (NULL == CU_add_test(pSuite, "testOSAL_Creat_worse", testOSAL_Creat_worse))||
        (NULL == CU_add_test(pSuite, "testOSAL_Creat_duplicate", testOSAL_Creat_duplicate))   ){
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}