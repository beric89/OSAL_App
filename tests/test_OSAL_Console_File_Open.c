/*
 * File:   test_OS_Open.c
 * Author: Luka Maletic
 *
 * Created on 22 Sep 2020, 09:34:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <CUnit/Basic.h>
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

// TODO: Trebaju bolji/deskriptivniji nazivi za testove (Izbjegavati numerisanje 1, 2, 3) 
void testOSAL_File_Open_worse() {
    char* name = "test4.txt";
    CU_ASSERT_EQUAL(OSAL_Console_File_Open(name), OSAL_Test_FAIL);
}

void testOSAL_File_Open_worse1() {
    char* name = "test44444444444";
    CU_ASSERT_EQUAL(OSAL_Console_File_Open(name), OSAL_Test_FAIL);
}

void testOSAL_File_Open_worse2() {
    char* name = "";
    CU_ASSERT_EQUAL(OSAL_Console_File_Open(name), OSAL_Test_FAIL);
}

void testOSAL_File_Open_correct() {
    char* name;
    char* access;
    name = OSAL_File_name;
    access = "r";
    HANDLE* result = OSAL_Create(name, access);
    CloseHandle(result);
    CU_ASSERT_EQUAL(OSAL_Console_File_Open(name), OSAL_Test_PASS);
    // BITNO BITNO BITNO
    // TODO: Ovo je generalno opasno raditi. Ne svidja mi se bas pristup sa ovim addressP, addressD... addressD je trenutno globalna i moze je svako mijenjati, nemamo bas dobru kotrolu nad njom.
    // Moze se desiti da se obrisu sistemski folderi itd...
    // Moracemo zajedno osmisliti i poraditi na tom mehanizmu (ako nista, pomocu nekih get funkcija... vidjecemo)
    DeleteFileA(addressP);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("test_OSAL_Console_File_Open", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testOSAL_File_Open_worse", testOSAL_File_Open_worse))||
        (NULL == CU_add_test(pSuite, "testOSAL_File_Open_worse1", testOSAL_File_Open_worse1))||
        (NULL == CU_add_test(pSuite, "testOSAL_File_Open_worse2", testOSAL_File_Open_worse2))||
        (NULL == CU_add_test(pSuite, "testOSAL_File_Open_correct", testOSAL_File_Open_correct))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}