/*
 * File:   test_FileSystem_Read.c
 * Author: Luka Maletic
 *
 * Created on 23 Sep 2020, 15:03:06
 */

#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <windows.h>
#include <string.h>
#include "../Windows\OSALInit.h"
/*
 * CUnit Test Suite
 */

static char addressP[OSAL_address_max_length];

int init_suite(void) {
    OSAL_APIInit();
    strcpy(addressP, addressD);
    strcat(addressP, OSAL_File_name);
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Read_correct() {
    HANDLE File = CreateFile(
            addressP,
            GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);
    
    char* buffer = OSAL_Read_text_correct;
    DWORD  dwBaytesWritten;
    
    int i = strlen(buffer)*sizeof(char);
    
    WriteFile(File, buffer, i, &dwBaytesWritten, NULL);
    
    CloseHandle(File);
    
    File = CreateFile(
            addressP,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);

    char bufferR[i];
    
    OSAL_Read(File, bufferR, i, OSAL_Read_position_correct);
    
    char bufferP[i-OSAL_Read_position_correct];
    for(int pom = 0; pom<(i-OSAL_Read_position_correct); pom = pom+1 )
    {
        bufferP[pom] = buffer[pom+OSAL_Read_position_correct];
    }
    bufferP[i-OSAL_Read_position_correct]='\0';
    CU_ASSERT_STRING_EQUAL(bufferR, bufferP);
  
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Read_not_exists_file() {
    HANDLE File = CreateFile(
            addressP,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    char* buffer = "test";
    int i = strlen(buffer)*sizeof(char);
    char bufferR[i];
    
    OSAL_Read(File, bufferR, i, 1);
    
    char bufferP[i-1];
    for(int pom = 0; pom<(i-1); pom = pom+1 )
    {
        bufferP[pom] = buffer[pom+1];
    }
    
    CU_ASSERT_STRING_NOT_EQUAL(bufferR, buffer);
   
    CloseHandle(File);
    DeleteFileA(addressP);
}

void testOSAL_Read_worse1() {
    char* buffer = OSAL_Read_text_correct;
    int i = strlen(buffer)*sizeof(char);
    HANDLE File;
    CU_ASSERT_EQUAL(OSAL_Read(File, buffer, i, OSAL_Read_position_worse), OSAL_Test_FAIL);   
}

void testOSAL_Read_worse2() {
    char* buffer = OSAL_Read_text_correct;
    int i = strlen(buffer)*sizeof(char);
    CU_ASSERT_EQUAL(OSAL_Read(NULL, buffer, i, OSAL_Read_position_correct), OSAL_Test_FAIL);   
}

void testOSAL_Read_worse3() {
    HANDLE File = CreateFile(
            addressP,
            GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CREATE_NEW,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);
    
    char* buffer = OSAL_Read_text_correct;
    DWORD  dwBaytesWritten;
    
    int i = strlen(buffer)*sizeof(char);
    
    WriteFile(File, buffer, i, &dwBaytesWritten, NULL);
    
    CloseHandle(File);
    
    File = CreateFile(
            addressP,
            GENERIC_READ,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL);
    
    CU_ASSERT_PTR_NOT_EQUAL(File, INVALID_HANDLE_VALUE);

    char bufferR[i];
    
    CU_ASSERT_EQUAL(OSAL_Read(File, bufferR, 50, OSAL_Read_position_correct), OSAL_Test_FAIL);
   
    CloseHandle(File);
    DeleteFileA(addressP);
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
    if ((NULL == CU_add_test(pSuite, "testOSAL_Read_correct", testOSAL_Read_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_not_exists_file", testOSAL_Read_not_exists_file))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_worse1", testOSAL_Read_worse1))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_worse2", testOSAL_Read_worse2))||
        (NULL == CU_add_test(pSuite, "testOSAL_Read_worse3", testOSAL_Read_worse3))    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}