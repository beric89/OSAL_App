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
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w+");

    CU_ASSERT_PTR_NOT_EQUAL(file, NULL);

    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    int bufferSizeInBytes = strlen(bufferToBeRead)*sizeof(char);

    fwrite(bufferToBeRead, bufferSizeInBytes, sizeof(char), file);
    fclose(file);

    file = fopen(filePath, "r");

    CU_ASSERT_PTR_NOT_EQUAL(file, NULL);

    char bufferRead[bufferSizeInBytes];

    CU_ASSERT_EQUAL(OSAL_Read(file, bufferRead, bufferSizeInBytes, OSAL_READ_POSITION_CORRECT), OSAL_OK);

    char bufferToBeReadWithPositionForRead[bufferSizeInBytes-OSAL_READ_POSITION_CORRECT];
    for(int pom = 0; pom<(bufferSizeInBytes-OSAL_READ_POSITION_CORRECT); pom = pom+1 )
    {
        bufferToBeReadWithPositionForRead[pom] = bufferToBeRead[pom+OSAL_READ_POSITION_CORRECT];
    }
    bufferToBeReadWithPositionForRead[bufferSizeInBytes-OSAL_READ_POSITION_CORRECT]='\0';
    CU_ASSERT_STRING_EQUAL(bufferRead, bufferToBeReadWithPositionForRead);

    fclose(file);
    remove(filePath);
}

void testOSAL_Read_position_invalid() {
    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);
    CU_ASSERT_EQUAL(OSAL_Read(NULL, bufferToBeRead, bufferSizeInBytes, OSAL_READ_POSITION_WRONG), OSAL_FAIL);
}

void testOSAL_Read_invalid_file_handle() {
    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);
    CU_ASSERT_EQUAL(OSAL_Read(NULL, bufferToBeRead, bufferSizeInBytes, OSAL_READ_POSITION_WRONG), OSAL_FAIL);
}

void testOSAL_Read_invalid_number_of_bytes() {
    char filePath[OSAL_PATH_MAX_LENGTH] = OSAL_APIINIT_ADDRESS;
    strcat(filePath, "\\");
    strcat(filePath, OSAL_FILE_NAME);
    FILE* file = fopen(filePath, "w+");

    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);

    char* bufferToBeRead = OSAL_READ_TEXT_CORRECT;
    int bufferSizeInBytes = strlen(bufferToBeRead) * sizeof(char);

    fwrite(bufferToBeRead, bufferSizeInBytes, sizeof(char), file);
    fclose(file);

    file = fopen(filePath, "r");

    CU_ASSERT_PTR_NOT_EQUAL(file, INVALID_HANDLE_VALUE);

    char bufferRead[bufferSizeInBytes];

    CU_ASSERT_EQUAL(OSAL_Read(file, bufferRead, bufferSizeInBytes+1, OSAL_READ_POSITION_CORRECT), OSAL_FAIL);

    fclose(file);
    remove(filePath);
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