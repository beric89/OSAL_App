#include <stdio.h>
#include <windows.h>
#include <conio.h> 
#include <string.h>
#include "console.h"
#include "OSALInit.h"

int OSAL_Printf (char *var)
{
    char text[200] = "String is: "; //TODO: consider using STRING_LIMIT 200
    strcat(text, var);
    
    if(en_dis == OSAL_APIInit_value_TRUE)
    {
	if ( WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), NULL, NULL) == FALSE )
	{
		if ( AllocConsole() == TRUE )
		{
			WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), text, strlen(text), NULL, NULL);

			getch();

			FreeConsole();
		}
	}
       else
               getch();
	return OSAL_Test_PASS;
    }
    else
    {
        return OSAL_Test_FAIL;
    }
}

void OSAL_PrintfDisable (void){ 
    en_dis = OSAL_APIInit_value_FALSE;
}

void OSAL_PrintfEnable (void){ 
    en_dis = OSAL_APIInit_value_TRUE;
}