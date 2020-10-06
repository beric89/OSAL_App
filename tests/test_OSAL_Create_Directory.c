/*
 * File:   test_OSAL_Create_Directory.c
 * Author: Luka Maletic
 *
 * Created on 28 Sep 2020, 08:21:41
 */

#include "../OSALTestHeader.h"
/*
 * CUnit Test Suite
 */

static char filePath[OSAL_PATH_MAX_LENGHT];

int init_suite(void) {
    OSAL_APIInit();
    strcpy(filePath, addressD);
    strcat(filePath, OSAL_DIRECORY_NAME);
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Create_Directory_valid_name() {
    CU_ASSERT_EQUAL(OSAL_CreateDirectory(OSAL_DIRECORY_NAME, ""), OSAL_OK);
    RemoveDirectoryA(filePath);
}

void testOSAL_Create_Directory_invalid_name() {
    CU_ASSERT_EQUAL(OSAL_CreateDirectory("", ""), OSAL_FAIL);
    RemoveDirectoryA(filePath);
}

void testOSAL_Create_Directory_name_too_long() {
    char name[OSAL_FILE_NAME_MAX_LENGHT+1];
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGHT+1>strlen(name))
    {
        name[i] = "a";
        i++;
    }
    CU_ASSERT_EQUAL(OSAL_CreateDirectory(name, ""), OSAL_FAIL);
    RemoveDirectoryA(filePath);
}

void testOSAL_Create_Directory_exists() {
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    CU_ASSERT_EQUAL(OSAL_CreateDirectory(OSAL_DIRECORY_NAME, ""), OSAL_FAIL);
    RemoveDirectoryA(filePath);
}

void testOSAL_Create_Directory_path_exists() {
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    strcat(filePath, "\\p");
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    strcat(filePath, "\\pp");
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    CU_ASSERT_EQUAL(OSAL_CreateDirectory(OSAL_DIRECORY_NAME, "TESTtest p"), OSAL_FAIL);
    CU_ASSERT_EQUAL(system("cd C:\\Temp\\ && rmdir /Q /S TESTtest"), 0);
}

void testOSAL_Create_Directory_path_not_exists() {
    CU_ASSERT_EQUAL(OSAL_CreateDirectory(OSAL_DIRECORY_NAME, "TESTtest p"), OSAL_FAIL);
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
    if ((NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_valid_name", testOSAL_Create_Directory_valid_name))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_invalid_name", testOSAL_Create_Directory_invalid_name))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_exists", testOSAL_Create_Directory_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_Directory_name_too_long", testOSAL_Create_Directory_name_too_long))    ||
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