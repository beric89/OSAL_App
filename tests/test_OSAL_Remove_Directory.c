/*
 * File:   test_OSAL_Remove_Directory.c
 * Author: Luka Maletic
 *
 * Created on 28 Sep 2020, 08:56:41
 */

#include "../OSALTestHeader.h"
/*
 * CUnit Test Suite
 */

int init_suite(void) {
    OSAL_APIInit();
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Remove_Directory_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "TESTtest");
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    CU_ASSERT_EQUAL(OSAL_RemoveDirectory("", OSAL_DIRECTORY_NAME), OSAL_OK);
}

void testOSAL_Remove_Directory_not_exists() {
    CU_ASSERT_EQUAL(OSAL_RemoveDirectory("" ,OSAL_DIRECTORY_NAME), OSAL_FAIL);
}

void testOSAL_Remove_Directory_name_too_short() {
    CU_ASSERT_EQUAL(OSAL_RemoveDirectory("", ""),OSAL_FAIL);
}

void testOSAL_Remove_Directory_multy_folders_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "TESTtest");
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    strcat(filePath, "\\p");
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    CU_ASSERT_EQUAL(OSAL_RemoveDirectory("TESTtest", "p"), OSAL_OK);
    CU_ASSERT_EQUAL(OSAL_RemoveDirectory("", OSAL_DIRECTORY_NAME), OSAL_OK);
}

void testOSAL_Remove_Directory_path_not_exists() {
    CU_ASSERT_EQUAL(OSAL_RemoveDirectory(OSAL_DIRECTORY_NAME, ""), OSAL_FAIL);
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
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_name_too_short", testOSAL_Remove_Directory_name_too_short)) ||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_Directory_multy_folders_correct", testOSAL_Remove_Directory_multy_folders_correct))||
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