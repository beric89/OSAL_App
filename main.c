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
    OSAL_Create_Directory("folder", "");
    OSAL_Create_Directory("opet", "");
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
    OSAL_Create_Directory("brisi", "");
    f = OSAL_Create("test.txt", "r/w");
    OSAL_Close(f);
    OSAL_Remove_Directory("brisi", "folder opet");
    OSAL_Open_Directory("opet", "folder");
    OSAL_Create_Directory("e", "");
    f = OSAL_Create("test.txt", "r/w");
    OSAL_Close(f);
    OSAL_Create_Directory("oop", "");
    return 0;
}

