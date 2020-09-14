/*
 * File:   test_OSAL_Create_Directory.c
 * Author: Luka Maletic
 *
 * Created on 28 Sep 2020, 08:21:41
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
    strcat(addressP, OSAL_Diretory_name);
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Create_Directory_correct() {
    CU_ASSERT_EQUAL(OSAL_Create_Directory(OSAL_Diretory_name, ""), OSAL_Test_PASS);
    RemoveDirectoryA(addressP);
}

void testOSAL_Create_Directory_worse() {
    CU_ASSERT_EQUAL(OSAL_Create_Directory("", ""), OSAL_Test_FAIL);
    RemoveDirectoryA(addressP);
}

void testOSAL_Create_Directory_exists() {
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    CU_ASSERT_EQUAL(OSAL_Create_Directory(OSAL_Diretory_name, ""), OSAL_Test_FAIL);
    RemoveDirectoryA(addressP);
}

void testOSAL_Create_Directory_path_exists() {
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    strcat(addressP, "\\p");
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    strcat(addressP, "\\pp");
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    CU_ASSERT_EQUAL(OSAL_Create_Directory(OSAL_Diretory_name, "TESTtest p"), OSAL_Test_FAIL);
    system("cd C:\\Temp\\ && rmdir /Q /S TESTtest");
}

void testOSAL_Create_Directory_path_not_exists() {
    CU_ASSERT_EQUAL(OSAL_Create_Directory(OSAL_Diretory_name, "TESTtest p"), OSAL_Test_FAIL);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Create_Directory", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_correct", testOSAL_Create_Directory_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_worse", testOSAL_Create_Directory_worse))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_exists", testOSAL_Create_Directory_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_path_exists", testOSAL_Create_Directory_path_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_path_not_exists", testOSAL_Create_Directory_path_not_exists))) 
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}