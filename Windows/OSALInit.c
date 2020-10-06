/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "OSALInit.h"
#include <stdio.h>
#include <string.h>

OSAL_ReturnType OSAL_APIInit (void){
    consoleEnabled = OSAL_CONSOLE_ENABLED;
    strcpy(address, OSAL_APIINIT_ADDRESS);
    strcpy(addressD, OSAL_APIINIT_ADDRESS);
    return OSAL_OK;
}