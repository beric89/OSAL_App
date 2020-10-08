/*
 * File:   test_FileSystem_Read.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 15:03:06
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

void testOSAL_Read_file_correct() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "C:\\Temp\\test.txt";
    HANDLE file = CreateFile(
            filePath,
            GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);
    
    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    DWORD  dwBaytesWritten;
    
    int bufferSizeInBytes = strlen(bufferToBeRead)*sizeof(char);
    
    WriteFile(file, bufferToBeRead, bufferSizeInBytes, &dwBaytesWritten, NULL);
    
    CloseHandle(file);
    
    file = CreateFile(
            filePath,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);

    char bufferRead[bufferSizeInBytes];
    
    OSAL_Read(file, bufferRead, bufferSizeInBytes, OSAL_READ_POSITION_CORRECT);
    
    char bufferToBeReadWithPositionForRead[bufferSizeInBytes-OSAL_READ_POSITION_CORRECT];
    for(int pom = 0; pom<(bufferSizeInBytes-OSAL_READ_POSITION_CORRECT); pom = pom+1 )
    {
        bufferToBeReadWithPositionForRead[pom] = bufferToBeRead[pom+OSAL_READ_POSITION_CORRECT];
    }
    bufferToBeReadWithPositionForRead[bufferSizeInBytes-OSAL_READ_POSITION_CORRECT]='\0';
    CU_ASSERT_STRING_EQUAL(bufferRead, bufferToBeReadWithPositionForRead);
  
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Read_not_exists_file() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "C:\\Temp\\test.txt";
    HANDLE file = CreateFile(
            filePath,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    char* bufferToBeRead = "test";
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);
    char bufferRead[bufferSizeInBytes];
    
    OSAL_Read(file, bufferRead, bufferSizeInBytes, 1);
    
    char bufferToBeReadWithPositionForRead[bufferSizeInBytes - 1];
    for(int i = 0; i < (bufferSizeInBytes - 1); i++)
    {
        bufferToBeReadWithPositionForRead[i] = bufferToBeRead[i + 1];
    }
    
    CU_ASSERT_STRING_NOT_EQUAL(bufferRead, bufferToBeRead);
   
    CloseHandle(file);
    DeleteFileA(filePath);
}

void testOSAL_Read_position_invalid() {
    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);
    HANDLE file;
    CU_ASSERT_EQUAL(OSAL_Read(file, bufferToBeRead, bufferSizeInBytes, OSAL_READ_POSITION_WRONG), OSAL_FAIL);
}

void testOSAL_Read_invalid_file_handle() {
    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);
    CU_ASSERT_EQUAL(OSAL_Read(NULL, bufferToBeRead, bufferSizeInBytes, OSAL_READ_POSITION_WRONG), OSAL_FAIL);
}

void testOSAL_Read_invalid_number_of_bytes() {
    const char filePath[OSAL_PATH_MAX_LENGTH] = "C:\\Temp\\test.txt";
    HANDLE file = CreateFile(
            filePath,
            GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);
    
    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    DWORD  dwBytesWritten;
    
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);
    
    WriteFile(file, bufferToBeRead, bufferSizeInBytes, &dwBytesWritten, NULL);
    
    CloseHandle(file);
    
    file = CreateFile(
            filePath,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);

    char bufferRead[bufferSizeInBytes];
    
    CU_ASSERT_EQUAL(OSAL_Read(file, bufferRead, bufferSizeInBytes+1, OSAL_READ_POSITION_CORRECT), OSAL_FAIL);
   
    CloseHandle(file);
    DeleteFileA(filePath);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Read", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Read_correct", testOSAL_Read_file_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_not_exists_file", testOSAL_Read_not_exists_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_position_invalid", testOSAL_Read_position_invalid))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_invalid_file_handle", testOSAL_Read_invalid_file_handle))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_invalid_number_of_bytes", testOSAL_Read_invalid_number_of_bytes))    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}