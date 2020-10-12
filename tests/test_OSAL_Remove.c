/*
 * File:   test_OS_Remove.c
 * Author: Luka Maletic
 *
 * Created on 22 Sep 2020, 10:53:11
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

void testOSAL_Remove_file_name_too_long() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char name[OSAL_FILE_NAME_MAX_LENGTH + 1];
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGTH + 1 > strlen(name))
    {
        name[i] = "a";
        i++;
    }
    CU_ASSERT_EQUAL(OSAL_Remove(filePath, name), OSAL_FAIL);
}

void testOSAL_Remove_file_name_too_short() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* name = "";
    CU_ASSERT_EQUAL(OSAL_Remove(filePath, name), OSAL_FAIL);
}

void testOSAL_Remove_file_not_exists() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* name = OSAL_FILE_NAME;
    CU_ASSERT_EQUAL(OSAL_Remove(filePath, name), OSAL_FAIL);
}

void testOSAL_Remove_file_with_read_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    fclose(file);
    CU_ASSERT_EQUAL(OSAL_Remove("", OSAL_FILE_NAME), OSAL_OK);
}

void testOSAL_Remove_file_with_write_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    fclose(file);
    CU_ASSERT_EQUAL(OSAL_Remove("", OSAL_FILE_NAME), OSAL_OK);
}

void testOSAL_Remove_file_with_read_and_write_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    fclose(file);
    CU_ASSERT_EQUAL(OSAL_Remove("", OSAL_FILE_NAME), OSAL_OK);
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
    if ((NULL == CU_add_test(pSuite, "testOSAL_Remove_file_name_too_long", testOSAL_Remove_file_name_too_long))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_file_name_too_short", testOSAL_Remove_file_name_too_short))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_file_not_exists", testOSAL_Remove_file_not_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_file_with_read_access_correct", testOSAL_Remove_file_with_read_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_file_with_write_access_correct", testOSAL_Remove_file_with_write_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Remove_file_with_read_and_write_access_correct", testOSAL_Remove_file_with_read_and_write_access_correct))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}