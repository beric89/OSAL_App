/*
 * File:   test_OS_Creeate.c
 * Author: Luka Maletic
 *
 * Created on 21 Sep 2020, 09:34:52
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

void testOSAL_Create_file_name_too_long() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char name[OSAL_FILE_NAME_MAX_LENGTH+1];
    char* access;
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGTH + 1 > strlen(name))
    {
        name[i] = "a";
        i++;
    }
    access = "r";
    HANDLE* file = OSAL_Create(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_file_name_too_short() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* name;
    char* access;
    name = "";
    access = "r";
    HANDLE* file = OSAL_Create(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_access_rights_missing() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* access;
    char* name;
    access = "";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_access_rights_incorrect() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "";
    char* access;
    char* name;
    access = "aa";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(filePath, name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_file_with_read_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, OSAL_FILE_NAME);
    char* access = "r";
    char* name = OSAL_FILE_NAME;
    char* path = "";
    HANDLE* file = OSAL_Create(path, name, access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Create_file_with_write_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, OSAL_FILE_NAME);
    char* access = "w";
    char* name = OSAL_FILE_NAME;
    char* path = "";
    HANDLE* file = OSAL_Create(path, name, access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Create_file_with_read_and_write_access_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, OSAL_FILE_NAME);
    char* access = "r/w";
    char* name = OSAL_FILE_NAME;
    char* path = "";
    HANDLE* file = OSAL_Create(path, name, access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Create_duplicate() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, OSAL_FILE_NAME);
    char* access = "r";
    char* name = OSAL_FILE_NAME;
    char* path = "";
    HANDLE* file = OSAL_Create(path, name, access);
    CU_ASSERT_PTR_NOT_NULL(file);

    char* name1 = OSAL_FILE_NAME;
    char* access1 = "r";
    char* path1 = "";
    HANDLE* file1 = OSAL_Create(path1, name1, access1);
    CU_ASSERT_PTR_NULL(file1);
    CloseHandle(file);
    CloseHandle(file1);
    DeleteFileA(filePath);
}

void testOSAL_Create_file_with_relative_path_correct() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "folder");
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    char* access = "r";
    char* name = OSAL_FILE_NAME;
    char* path = "folder";
    HANDLE* file = OSAL_Create(path, name, access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    CU_ASSERT_EQUAL(system("cd C:\\Temp\\ && rmdir /Q /S folder"), 0);
}

void testOSAL_Create_no_path() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "test path";
    char* access;
    char* name;
    access = "r";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(filePath,name,access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
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
    if ((NULL == CU_add_test(pSuite, "testOSAL_Create_file_name_too_long", testOSAL_Create_file_name_too_long))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_file_name_too_short", testOSAL_Create_file_name_too_short))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_access_rights_missing", testOSAL_Create_access_rights_missing))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_access_rights_incorrect", testOSAL_Create_access_rights_incorrect)) ||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_file_with_read_access_correct", testOSAL_Create_file_with_read_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_file_with_write_access_correct", testOSAL_Create_file_with_write_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_file_with_read_and_write_access_correct", testOSAL_Create_file_with_read_and_write_access_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_duplicate", testOSAL_Create_duplicate))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_file_with_relative_path_correct", testOSAL_Create_file_with_relative_path_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Create_no_path", testOSAL_Create_no_path))   ){
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}