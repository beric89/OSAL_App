/*
 * File:   test_FileSystem_Close_correct.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 13:54:04
 */

#include "../OSALTestHeader.h"
#include "../Windows\OSALInit.h"
#include "../Windows\filesystem.h"


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

void testOSAL_Close_read_file() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    fclose(file);
    file = fopen(filePath, "r");
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_OK);
    remove(filePath);
}

void testOSAL_Close_write_file() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w");
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_OK);
    remove(filePath);
}

void testOSAL_Close_read_or_write_file() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w+");
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_OK);
    remove(filePath);
}

void testOSAL_Close_invalid_file_handle() {
    CU_ASSERT_EQUAL(OSAL_Close(NULL), OSAL_FAIL);
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
    if ((NULL == CU_add_test(pSuite, "testOSAL_Close_read_file", testOSAL_Close_read_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Close_write_file", testOSAL_Close_write_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Close_read_or_write_file", testOSAL_Close_read_or_write_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Close_invalid_file_handle", testOSAL_Close_invalid_file_handle))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}