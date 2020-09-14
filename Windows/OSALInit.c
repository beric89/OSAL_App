/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "OSALInit.h"
#include <stdio.h>
#include <string.h>

int OSAL_APIInit (void){
    en_dis = OSAL_APIInit_value_TRUE;
    strcpy(address, OSAL_APIInit_address);
    strcpy(addressD, OSAL_APIInit_address);
    return OSAL_Test_PASS;
}