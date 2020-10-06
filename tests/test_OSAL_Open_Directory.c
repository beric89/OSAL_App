/*
 * File:   test_OSAL_Open_Directory.c
 * Author: Luka Maletic
 *
 * Created on 28 Sep 2020, 12:12:47
 */

#include "../OSALTestHeader.h"
/*
 * CUnit Test Suite
 */

static char filePath[OSAL_PATH_MAX_LENGHT];

int init_suite(void) {
    OSAL_APIInit();
    strcpy(filePath, addressD);
    strcat(filePath, OSAL_DIRECORY_NAME);
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testOSAL_Open_Directory_correct() {
    CU_ASSERT_TRUE(CreateDirectoryA(filePath, NULL));
    CU_ASSERT_EQUAL(OSAL_OpenDirectory(OSAL_DIRECORY_NAME, ""), OSAL_OK);
    CU_ASSERT_TRUE(RemoveDirectoryA(filePath));
}

void testOSAL_Open_Directory_file_name_and_path_missing() {
    CU_ASSERT_EQUAL(OSAL_OpenDirectory("", ""), OSAL_FAIL);
}

void testOSAL_Open_Directory_not_exists() {
    CU_ASSERT_EQUAL(OSAL_OpenDirectory(OSAL_DIRECORY_NAME, ""), OSAL_FAIL);
}

void testOSAL_Open_Directory_path_not_exists() {
    CU_ASSERT_EQUAL(OSAL_OpenDirectory(OSAL_DIRECORY_NAME, "Test test"), OSAL_FAIL);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Open_Directory", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_Open_Directory_correct", testOSAL_Open_Directory_correct))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_Directory_file_name_and_path_missing", testOSAL_Open_Directory_file_name_and_path_missing))    ||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_Directory_not_exists", testOSAL_Open_Directory_not_exists))||
        (NULL == CU_add_test(pSuite, "testOSAL_Open_Directory_path_not_exists", testOSAL_Open_Directory_path_not_exists))    ) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}