/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   OSALTestHeader.h
 * Author: Luka Maletic
 *
 * Created on 6 October 2020, 13:33
 */

#ifndef OSALTESTHEADER_H
#define OSALTESTHEADER_H

#ifdef __cplusplus
extern "C" {
#endif
    
#define OSAL_FILE_NAME "test.txt"
#define OSAL_DIRECORY_NAME "TESTtest"
#define OSAL_PRINTF_STRING "test test test"
#define OSAL_READ_TEXT_CORRECT "TEST TEST TEST TEST!"
#define OSAL_WRITE_TEXT "Test test test test!"
#define OSAL_READ_POSITION_WORSE 50
#define OSAL_READ_POSITION_CORRECT 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <CUnit/Basic.h>
#include "Windows\OSALInit.h"
#include "Windows\clock.h"



#ifdef __cplusplus
}
#endif

#endif /* OSALTESTHEADER_H */

