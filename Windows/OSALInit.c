/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "OSALInit.h"
#include <stdio.h>
#include <string.h>

int OSAL_APIInit (void){
    // pogledati OSALInit.h komentar za enum
    en_dis = OSAL_CONSOLE_ENABLED;
    strcpy(address, OSAL_APIInit_address);
    strcpy(addressD, OSAL_APIInit_address);
    // TODO: Koristiti nesto sto nece imati naziv test u sebi. Npr:
    return OSAL_OK;
}