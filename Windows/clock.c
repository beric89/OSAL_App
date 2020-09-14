#include <stdio.h>
#include <windows.h>
#include "clock.h"

int* OSAL_GetLocalTime (void){
    SYSTEMTIME t;
    GetLocalTime(&t);
    static int pom[6];
    pom[0] = t.wYear;
    pom[1] = t.wMonth;
    pom[2] = t.wDay;
    pom[3] = t.wHour;
    pom[4] = t.wMinute;
    pom[5] = t.wSecond;
    pom[6] = t.wMilliseconds;
    return pom;
}

void OSAL_SetLocalTime (int*date){
    SYSTEMTIME t;
    t.wYear = date[0];
    t.wMonth = date[1];
    t.wDay = date[2];
    t.wHour = date[3];
    t.wMinute = date[4];
    t.wSecond = date[5];
    t.wMilliseconds = date[6];
    SetLocalTime(&t);
}