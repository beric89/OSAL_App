#include <windows.h>
// TODO: Primijetio sam da u console i clock, funkcije imaju nazive u camel case-u. Npr OSAL_GetLocalTime, dok su ovdje rijeci razdvojene sa '_'. Prepraviti u OSAL_ConsoleFileOpen, OSAL_CreateDirectory...
HANDLE* OSAL_Create(char* ,char* );

int OSAL_ConsoleFileOpen(char* );

int OSAL_Remove(char* );

HANDLE* OSAL_Open(char*, char* );

int OSAL_Close(HANDLE* );

int OSAL_Write(HANDLE* ,char* );

int OSAL_Read(HANDLE* ,char*, int, int);

int OSAL_CreateDirectory(char *, char*);

int OSAL_RemoveDirectory(char *, char*);

int OSAL_OpenDirectory(char*, char*);

