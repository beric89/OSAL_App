#include <stdio.h>
#include <windows.h>
#include "clock.h"

OSAL_TimeType OSAL_GetLocalTime (void){
    SYSTEMTIME t;
    GetLocalTime(&t);
    struct OSAL_TimeType time;
    time.year = t.wYear;
    time.month = t.wMonth;
    time.day = t.wDay;
    time.hour = t.wHour;
    time.minute = t.wMinute;
    time.second = t.wSecond;
    time.milliseconds = t.wMilliseconds;
    return time;
}

void OSAL_SetLocalTime (OSAL_TimeType time){
    SYSTEMTIME t;
    t.wYear = time.year;
    t.wMonth = time.month;
    t.wDay = time.day;
    t.wHour = time.hour;
    t.wMinute = time.minute;
    t.wSecond = time.second;
    t.wMilliseconds = time.milliseconds;
    SetLocalTime(&t);
}