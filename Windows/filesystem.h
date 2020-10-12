#ifndef OSAL_FILESYSTEM_H
#define OSAL_FILESYSTEM_H
#include <stdio.h>
#include "OSALInit.h"

FILE* OSAL_Create(char* ,char*, char* );

OSAL_ReturnType OSAL_ConsoleFileOpen(char* , char* );

OSAL_ReturnType OSAL_Remove(char* filePath, char* name);

FILE* OSAL_Open(char* ,char*, char* );

OSAL_ReturnType OSAL_Close(FILE* );

OSAL_ReturnType OSAL_Write(FILE* ,char* );

OSAL_ReturnType OSAL_Read(FILE* ,char*, int, int);

OSAL_ReturnType OSAL_CreateDirectory(char *, char*);

OSAL_ReturnType OSAL_RemoveDirectory(char *, char*);

#endif // OSAL_FILESYSTEM_H