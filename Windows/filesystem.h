#ifndef OSAL_FILESYSTEM_H
#define OSAL_FILESYSTEM_H

#include <windows.h>
#include "OSALInit.h"

// TODO: Pogledao samo ovo detaljnije, moracemo napraviti da radi sa FILE*, posto je ovo interfejs. Ne smiju biti
//  include-ovi vezani za neki OS ovdje (windows.h).
// -Funkcije ce da primaju i vracaju FILE* umjesto HANDLE*
// -Napraviti 2 pomocne, staticke funckije koje od FILE* prave HANDLE* i od HANDLE* prave FILE*
// -unutar OSAL_Close, OSAL_Write, OSAL_Read odraditi na pocetku konverziju FILE*->HANDLE*. Ostatak implementacije ce ostati isti
// -unutar OSAL_Create i OSAL_Open odraditi konverziju HANDLE*->FILE* na kraju
// (https://www.codeproject.com/Articles/1044/A-Handy-Guide-To-Handling-Handles)

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