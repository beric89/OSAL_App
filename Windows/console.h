#ifndef OSAL_CONSOLE_H 
#define OSAL_CONSOLE_H

#include "OSALInit.h"

OSAL_ReturnType OSAL_Printf (char*);

void OSAL_PrintfDisable (void);

void OSAL_PrintfEnable (void);

#endif // OSAL_CONSOLE_H