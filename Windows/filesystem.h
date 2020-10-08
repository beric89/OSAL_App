#ifndef OSAL_FILESYSTEM_H  
#define OSAL_FILESYSTEM_H 

#include <windows.h>
#include "OSALInit.h"

HANDLE* OSAL_Create(char* ,char*, char* );

OSAL_ReturnType OSAL_ConsoleFileOpen(char* , char* );

OSAL_ReturnType OSAL_Remove(char* filePath, char* name);

HANDLE* OSAL_Open(char* ,char*, char* );

OSAL_ReturnType OSAL_Close(HANDLE* );

OSAL_ReturnType OSAL_Write(HANDLE* ,char* );

OSAL_ReturnType OSAL_Read(HANDLE* ,char*, int, int);

OSAL_ReturnType OSAL_CreateDirectory(char *, char*);

OSAL_ReturnType OSAL_RemoveDirectory(char *, char*);

#endif // OSAL_FILESYSTEM_H 