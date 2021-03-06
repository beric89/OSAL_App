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

static char filePath[OSAL_PATH_MAX_LENGTH];

int init_suite(void) {
    OSAL_APIInit();
    strcpy(filePath, addressD);
    strcat(filePath, OSAL_FILE_NAME);
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Remove_file_name_too_long() {
    char name[OSAL_FILE_NAME_MAX_LENGHT+1];
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGHT+1>strlen(name))
    {
        name[i] = "a";
        i++;
    }
    CU_ASSERT_EQUAL(OSAL_Remove(name), OSAL_FAIL);
}

void testOSAL_Remove_file_name_too_short() {
    char* name = "";
    CU_ASSERT_EQUAL(OSAL_Remove(name),OSAL_FAIL);
}

void testOSAL_Remove_file_not_exists() {
    char* name = OSAL_FILE_NAME;
    CU_ASSERT_EQUAL(OSAL_Remove(name), OSAL_FAIL);
}

void testOSAL_Remove_file_with_read_access_correct() {
    HANDLE file = CreateFile(
        filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CloseHandle(file);
    CU_ASSERT_EQUAL(OSAL_Remove(OSAL_FILE_NAME), OSAL_OK);
}

void testOSAL_Remove_file_with_write_access_correct() {
    OSAL_APIInit();
    HANDLE file = CreateFile(
        filePath,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CloseHandle(file);
    CU_ASSERT_EQUAL(OSAL_Remove(OSAL_FILE_NAME), OSAL_OK);
}

void testOSAL_Remove_file_with_read_and_write_access_correct() {
    OSAL_APIInit();
    HANDLE file = CreateFile(
        filePath,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    CloseHandle(file);
    CU_ASSERT_EQUAL(OSAL_Remove(OSAL_FILE_NAME), OSAL_OK);
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