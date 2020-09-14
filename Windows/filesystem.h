#include <windows.h>

HANDLE* OSAL_Create(char* ,char* );

int OSAL_Console_File_Open(char* );

int OSAL_Remove(char* );

HANDLE* OSAL_Open(char*, char* );

int OSAL_Close(HANDLE* );

int OSAL_Write(HANDLE* ,char* );

int OSAL_Read(HANDLE* ,char*, int, int);

int OSAL_Create_Directory(char *, char*);

int OSAL_Remove_Directory(char *, char*);

int OSAL_Open_Directory(char*, char*);

