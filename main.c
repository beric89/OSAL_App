/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Luka Maletic
 *
 * Created on 14 September 2020, 10:40
 */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <winbase.h>
#include <windows.h>
#include <string.h>
#include "OSAL.h"


/*
 * 
 */


int main(void){
    OSAL_APIInit();
    OSAL_CreateDirectory("folder", "");
    OSAL_CreateDirectory("opet", "");
    HANDLE f = OSAL_Create("test.txt", "r/w");
    OSAL_Close(f);
    f = OSAL_Open("test.txt", "w");
    OSAL_Write(f, "test test test!");
    OSAL_Close(f);
    f = OSAL_Open("test.txt", "r");
    char buffer[15];
    OSAL_Read(f, buffer, GetFileSize(f, NULL), 2);
    printf("%s\n", buffer);
    OSAL_Close(f);
    OSAL_CreateDirectory("brisi", "");
    f = OSAL_Create("test.txt", "r/w");
    OSAL_Close(f);
    OSAL_RemoveDirectory("brisi", "folder opet");
    OSAL_OpenDirectory("opet", "folder");
    OSAL_CreateDirectory("e", "");
    f = OSAL_Create("test.txt", "r/w");
    OSAL_Close(f);
    OSAL_CreateDirectory("oop", "");
    return 0;
}

