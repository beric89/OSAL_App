#include <stdio.h>
#include <windows.h>
#include <conio.h> 
#include <string.h>
#include "console.h"
#include "OSALInit.h"

// TODO: koristiti deskriptivniju varijablu, umjesto var. npr textToPrint ili sl.
int OSAL_Printf (char* var)
{
    // TODO: umjesto jednostavnog 'String is: ', dodati barem 'OSAL: '.
    // NOTE: Ako bude vremena, dodacemo __LINE__ i __FILE__ ispise
    char consoleText[OSAL_PRINTF_TEXT_MAX_LENGTH] = "String is: ";
    strcat(consoleText, var);
    
    if(en_dis == OSAL_APIInit_value_TRUE)
    {
	if ( WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), consoleText, strlen(consoleText), NULL, NULL) == FALSE )
	{
		if ( AllocConsole() == TRUE )
		{
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), consoleText, strlen(consoleText), NULL, NULL);

			getch();

			FreeConsole();
		}
	} // TODO: Cudno poravnanje za else uslov, popraviti. Takodje, else treba da ima '{' i '}', bez obzira koliko naredbi u njemu bilo
       else
               getch();
	return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

void OSAL_PrintfDisable (void){ 
    en_dis = OSAL_APIInit_value_FALSE;
}

void OSAL_PrintfEnable (void){ 
    en_dis = OSAL_APIInit_value_TRUE;
}