/*
 * File:   test_FileSystem_Close_correct.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 13:54:04
 */

#include "../OSALTestHeader.h"

/*
 * CUnit Test Suite
 */

static char filePath[OSAL_PATH_MAX_LENGHT];

int init_suite(void) {
    OSAL_APIInit();
    strcpy(filePath, addressD);
    strcat(filePath, OSAL_FILE_NAME);
    return 0;
}

int clean_suite(void) {
    DeleteFileA(filePath);
    return 0;
}

void testOSAL_Close_read_file() {
    HANDLE file = CreateFile(
        filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_OK);
}

void testOSAL_Close_write_file() {
    HANDLE file = CreateFile(
        filePath,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_OK);
}

void testOSAL_Close_read_or_write_file() {
    HANDLE file = CreateFile(
        filePath,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_OK);
}

void testOSAL_Close_invalid_file_handle() {
    HANDLE file;
    int result = OSAL_Close(file);
    CU_ASSERT_EQUAL(OSAL_Close(file), OSAL_FAIL);
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