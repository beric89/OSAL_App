#ifndef OSAL_CONSOLE_H  
#define OSAL_CONSOLE_H 

typedef struct OSAL_TimeType{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int milliseconds;
}OSAL_TimeType;

OSAL_TimeType OSAL_GetLocalTime (void);

void OSAL_SetLocalTime (struct OSAL_TimeType);

#endif // OSAL_CONSOLE_H
