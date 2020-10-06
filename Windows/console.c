#include <stdio.h>
#include <windows.h>
#include <conio.h> 
#include <string.h>
#include "console.h"

OSAL_ReturnType OSAL_Printf (char* textToPrintf)
{
    char consoleText[OSAL_PRINTF_TEXT_MAX_LENGTH] = "OSAL string is: ";
    strcat(consoleText, textToPrintf);
    
    if(consoleEnabled == OSAL_CONSOLE_ENABLED)
    {
	if ( WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), consoleText, strlen(consoleText), NULL, NULL) == FALSE )
	{
            if ( AllocConsole() == TRUE )
            {
                WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), consoleText, strlen(consoleText), NULL, NULL);
		getch();
		FreeConsole();
            }
	} 
        else
        {
            getch();
        }
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

void OSAL_PrintfDisable (void){ 
    consoleEnabled = OSAL_CONSOLE_DISABLED;
}

void OSAL_PrintfEnable (void){ 
    consoleEnabled = OSAL_CONSOLE_ENABLED;
}