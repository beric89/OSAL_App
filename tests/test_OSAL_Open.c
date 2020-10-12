/*
 * File:   test_FileSystem_Open.c
 * Author: Luka Maletic
 *
 * Created on 22 Sep 2020, 16:01:06
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

void testOSAL_Open_file_not_exists() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* name = OSAL_FILE_NAME;
    char* access = "w";
    FILE* file = OSAL_Open(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    fclose(file);
}

void testOSAL_Open_file_name_too_long() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char name[OSAL_FILE_NAME_MAX_LENGTH + 1];
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGTH + 1 > strlen(name))
    {
        name[i] = "a";
        i++;
    }
    char* access = "w";
    FILE* file = OSAL_Open(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    fclose(file);
}

void testOSAL_Open_file_name_too_short() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* name = "";
    char* access = "w";
    FILE* file = OSAL_Open(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    fclose(file);
}

void testOSAL_Open_access_rights_missing() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* name = OSAL_FILE_NAME;
    char* access = "";
    FILE* file = OSAL_Open(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    fclose(file);
}

void testOSAL_Open_file_with_read_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    HANDLE hFile = CreateFile(
        filePath,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    CloseHandle(hFile);

    FILE* file = OSAL_Open("", OSAL_FILE_NAME, "r");
    CU_ASSERT_PTR_NOT_EQUAL(file, ERROR_FILE_NOT_FOUND);
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);
    CU_ASSERT_PTR_NOT_NULL(file);
    fclose(file);
    DeleteFileA(filePath);
}

void testOSAL_Open_file_with_write_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    HANDLE hFile = CreateFile(
        filePath,
        GENERIC_WRITE,
        FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    CloseHandle(hFile);

    FILE* file = OSAL_Open("", OSAL_FILE_NAME, "r");
    CU_ASSERT_PTR_NOT_EQUAL(file, ERROR_FILE_NOT_FOUND);
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);
    CU_ASSERT_PTR_NOT_NULL(file);
    fclose(file);
    DeleteFileA(filePath);
}

void testOSAL_Open_file_with_read_and_write_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    HANDLE hFile = CreateFile(
        filePath,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    CloseHandle(hFile);

    FILE* file = OSAL_Open("", OSAL_FILE_NAME, "r");
    CU_ASSERT_PTR_NOT_EQUAL(file, ERROR_FILE_NOT_FOUND);
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);
    CU_ASSERT_PTR_NOT_NULL(file);
    fclose(file);
    DeleteFileA(filePath);
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
    if ((NULL == CU_add_test(pSuite, "testOSAL_Open_file_not_exists", testOSAL_Open_file_not_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_file_name_too_long", testOSAL_Open_file_name_too_long))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_file_name_too_short", testOSAL_Open_file_name_too_short))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_access_rights_missing", testOSAL_Open_access_rights_missing))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_file_with_read_access_correct", testOSAL_Open_file_with_read_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_file_with_write_access_correct", testOSAL_Open_file_with_write_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_file_with_read_and_write_access_correct", testOSAL_Open_file_with_read_and_write_access_correct))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}