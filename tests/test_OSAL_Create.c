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

// static char filePath[OSAL_PATH_MAX_LENGTH];

int init_suite(void) {
    OSAL_APIInit();
    // strcpy(filePath, addressD);
    // strcat(filePath, OSAL_FILE_NAME);
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Create_file_name_too_long() {
    char name[OSAL_FILE_NAME_MAX_LENGHT+1];
    char* access;
    int i = 0;
    while(OSAL_FILE_NAME_MAX_LENGHT+1>strlen(name))
    {
        name[i] = "a";
        i++;
    }
    access = "r";
    HANDLE* file = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_file_name_too_short() {
    char* name;
    char* access;
    name = "";
    access = "r";
    HANDLE* file = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_access_rights_missing() {
    char* access;
    char* name;
    access = "";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_access_rights_incorrect() {
    char* access;
    char* name;
    access = "aa";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(name, access);
    CU_ASSERT_PTR_NULL(file);
    CloseHandle(file);
}

void testOSAL_Create_file_with_read_access_correct() {
    char* access;
    char* name;
    access = "r";
    name = OSAL_FILE_NAME;

    HANDLE* file = OSAL_Create(name,access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Create_file_with_write_access_correct() {
    char* access,* name;
    access = "w";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(name,access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Create_file_with_read_and_write_access_correct() {
    char* access;
    char* name;
    access = "r/w";
    name = OSAL_FILE_NAME;
    HANDLE* file = OSAL_Create(name,access);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Create_duplicate() {
    char* name = OSAL_FILE_NAME;
    char* access = "r";
    HANDLE* file = OSAL_Create(name, access);
    CU_ASSERT_PTR_NOT_NULL(file);
    
    char* name1 = OSAL_FILE_NAME;
    char* access1 = "r";
    HANDLE* file1 = OSAL_Create(name1, access1);
    CU_ASSERT_PTR_NULL(file1);        
    CloseHandle(file);
    CloseHandle(file1);
    DeleteFileA(filePath);
}

void testOSAL_Create_file_with_relative_path_correct() {
    char fileName[OSAL_FILE_NAME_MAX_LENGHT] = "FolderA\\";
    strcat(filePath, OSAL_FILE_NAME);
    char* fileAccess = "r";
    // if neccessary create FolderA here
    HANDLE* file = OSAL_Create(fileName, fileAccess);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(fileName);
}

void testOSAL_Create_file_with_absolute_path_correct() {
    char[OSAL_FILE_NAME_MAX_LENGHT] fileName = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "FolderA\\");
    strcat(filePath, OSAL_FILE_NAME);
    char* fileAccess = "r";
    // if neccessary create FolderA here
    HANDLE* file = OSAL_Create(fileName, fileAccess);
    CU_ASSERT_PTR_NOT_NULL(file);
    CloseHandle(file);
    DeleteFileA(fileName);
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
        (NULL == CU_add_test(pSuite, "testOSAL_Create_duplicate", testOSAL_Create_duplicate))   ){
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}