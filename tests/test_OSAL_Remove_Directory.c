/*
 * File:   test_OSAL_Remove_Directory.c
 * Author: Luka Maletic
 *
 * Created on 28 Sep 2020, 08:56:41
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
    strcat(addressP, OSAL_Diretory_name);
    return 0;
}

int clean_suite(void) {
    return 0;
}

// TODO: Bolje nazive za testove. Pogledati test OSAL_Create komentare
void testOSAL_Remove_Directory_correct() {
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    CU_ASSERT_EQUAL(OSAL_Remove_Directory(OSAL_Diretory_name, ""), OSAL_Test_PASS);
}

void testOSAL_Remove_Directory_not_exists() {
    CU_ASSERT_EQUAL(OSAL_Remove_Directory(OSAL_Diretory_name, ""), OSAL_Test_FAIL);
}

void testOSAL_Remove_Directory_worse() {
    CU_ASSERT_EQUAL(OSAL_Remove_Directory("", ""),OSAL_Test_FAIL);
}

void testOSAL_Remove_Directory_correct1() {
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    strcat(addressP, "\\p");
    CU_ASSERT_TRUE(CreateDirectoryA(addressP, NULL));
    CU_ASSERT_EQUAL(OSAL_Remove_Directory("p", "TESTtest"), OSAL_Test_PASS);    
    CU_ASSERT_EQUAL(OSAL_Remove_Directory(OSAL_Diretory_name, ""), OSAL_Test_PASS); 
}

void testOSAL_Remove_Directory_path_not_exists() {
    CU_ASSERT_EQUAL(OSAL_Remove_Directory("p", "TESTtest"), OSAL_Test_FAIL);    
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Remove_Directory", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_correct", testOSAL_Remove_Directory_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_not_exists", testOSAL_Remove_Directory_not_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_worse", testOSAL_Remove_Directory_worse)) ||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_correct1", testOSAL_Remove_Directory_correct1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_path_not_exists", testOSAL_Remove_Directory_path_not_exists))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}