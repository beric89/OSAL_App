#include "filesystem.h"
#include <stdlib.h>
#include <string.h>


static OSAL_ReturnType nameValidation(char *name){
    if(strlen(name) == OSAL_FILE_NAME_MIN_LENGHT || strlen(name) > OSAL_FILE_NAME_MAX_LENGHT)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

static OSAL_ReturnType accessValidation(char *access){
    if( !strcmp(access, "r") || !strcmp(access, "w") || !strcmp(access, "r/w"))
    {
        return OSAL_OK;
    }
    else 
    {
        return OSAL_FAIL;
    }
}

static OSAL_ReturnType checkIfFileExists(char* fileName){
    char fname[OSAL_FILE_NAME_MAX_LENGHT];
    strcpy(fname, fileName);
    char filePathExists[OSAL_PATH_MAX_LENGHT] = "cd ";
    strcat(filePathExists, addressD);
    strcat(filePathExists, " && IF EXIST ");
    strcat(filePathExists, fname);
    strcat(filePathExists, " EXIT 1");
    int var = system(filePathExists);
    if(var == OSAL_TRUE)
    {
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

static OSAL_ReturnType checkIfDirectoryExists(char* directoryName, char* path){
    char directoryPathExists[OSAL_PATH_MAX_LENGHT] = "cd ";
    strcat(directoryPathExists, address);
    strcat(directoryPathExists, path);
    strcat(directoryPathExists, " && IF EXIST ");
    strcat(directoryPathExists, directoryName);
    strcat(directoryPathExists, " EXIT 2");
    if(system(directoryPathExists) == OSAL_DIRECTORY_EXISTS)
    {
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

static OSAL_ReturnType checkFileHandle(HANDLE* file)
{
    if(file == INVALID_HANDLE_VALUE)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

static DWORD setFileAccess(char* access, DWORD* generic)
{
    DWORD fileShareWrite;
    if (!strcmp(access, "r"))
    {
        fileShareWrite = FILE_SHARE_READ;
        *generic = GENERIC_READ;
    }
    else if(!strcmp(access, "w"))
    {
        fileShareWrite = FILE_SHARE_WRITE;
        *generic = GENERIC_WRITE;
    }
     else
    {
        fileShareWrite = FILE_SHARE_READ | FILE_SHARE_WRITE;
        *generic = GENERIC_READ | GENERIC_WRITE;
    }
    return fileShareWrite;
}

static void makeAddress(char* addressP, char* name)
{
    strcpy(addressP, addressD);
    strcat(addressP, name);
}

static char* makePath(char* path)
{
    static char newPath[OSAL_PATH_MAX_LENGHT];
    char newc = '\\';
    char old = ' ';
    int i = 0, j = 0;
    while(path[i]!='\0')
    {
        if(path[i] == old)
        {
            newPath[j++] = newc;
            newPath[j++] = newc;
        }
        else
        {
            newPath[j++] = path[i];   
        }
        i++;
    }
    newPath[j++] = '\0';
    return newPath;
}

HANDLE* OSAL_Create(char* name,char* access){
    char fileAddress[OSAL_PATH_MAX_LENGHT];
    makeAddress(fileAddress, name);
    if (nameValidation(name) == OSAL_FAIL)
    {
        return NULL;
    }
    if (accessValidation(access) == OSAL_FAIL)
    {
        return NULL;
    }
    if (checkIfFileExists(name) == OSAL_OK)
    {
        return NULL;
    }
    
    DWORD generic;
    DWORD fileShareWrite = setFileAccess(access, &generic);  
    HANDLE file = CreateFile(
        fileAddress,
        generic,
        fileShareWrite, 
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if(checkFileHandle(file) == OSAL_OK)
    {
        return file;
    }
    else
    {
        return NULL;
    }
}

OSAL_ReturnType OSAL_ConsoleFileOpen(char* fileName){
    if (nameValidation(fileName) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    
    if (checkIfFileExists(fileName) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    
    char filePath[OSAL_PATH_MAX_LENGHT] = "cd ";
    strcat(filePath, addressD);
    strcat(filePath, " && ");
    strcat(filePath, fileName);
    if((system(filePath) == 0))
    {
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

OSAL_ReturnType OSAL_Remove(char* name){
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    
    if (checkIfFileExists(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    char file[OSAL_PATH_MAX_LENGHT];
    strcpy(file, addressD);
    strcat(file, name);
    if(DeleteFileA(file) == 0)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

HANDLE* OSAL_Open(char* name, char* access)
{
    if (nameValidation(name) != OSAL_OK)
    {
        return NULL;
    }
    if (accessValidation(access) == OSAL_FAIL)
    {
        return NULL;
    }
    if (checkIfFileExists(name) == OSAL_FAIL)
    {
        return NULL;
    }
   
    char addressP[OSAL_PATH_MAX_LENGHT];
    makeAddress(addressP, name);
    
    DWORD generic;
    DWORD fileShareWrite = setFileAccess(access, &generic);    
 
    HANDLE File = CreateFile(
        addressP,
        generic,
        fileShareWrite, 
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
 
    if(checkFileHandle(File) == OSAL_OK)
    {
        return File;
    }
    else
    {
        return NULL;
    }  
}

OSAL_ReturnType OSAL_Close(HANDLE* file)
{
    if(CloseHandle(file) == 0)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
    
}

OSAL_ReturnType OSAL_Write(HANDLE* file, char* buffer)
{
    if (strlen(buffer) == OSAL_FALSE)
    {
        return OSAL_FAIL;
    }
    
    DWORD dwBytesToWrite = (DWORD)strlen(buffer);
    DWORD dwBytesWritten = 0;
    
    int writeResult = WriteFile(
                    file,
                    buffer,
                    dwBytesToWrite,
                    &dwBytesWritten,
                    NULL);

    if (writeResult == OSAL_FALSE)
    {
        return OSAL_FAIL;
    }
    else
    {
        if (dwBytesWritten != dwBytesToWrite)
        {
            return OSAL_FAIL;
        }
        else
        {
            return OSAL_OK;
        }
    }
}

OSAL_ReturnType OSAL_Read(HANDLE* File, char* buffer, int numberOfBytesToRead, int position)
{
   if(position > numberOfBytesToRead)
   {
       return OSAL_FAIL;
   }
   if(File == NULL)
   {
       return OSAL_FAIL;
   }
   if(numberOfBytesToRead > GetFileSize(File, NULL))
   {
       return OSAL_FAIL;
   }
   SetFilePointer(File, position, NULL, 0);
   DWORD dwBytesRead;
   ReadFile(File, buffer, numberOfBytesToRead - position, &dwBytesRead, NULL);
   buffer[numberOfBytesToRead - position] = '\0';
   return OSAL_OK;
}

OSAL_ReturnType OSAL_CreateDirectory(char* name, char* path)
{
    char* directoryPath = makePath(path);
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    
    if (checkIfDirectoryExists(name, directoryPath) == OSAL_OK)
    {
        return OSAL_FAIL;
    }
   
    char pathName[OSAL_PATH_MAX_LENGHT];
    strcpy(pathName, addressD);
    strcat(pathName, directoryPath);
    strcat(pathName, name);
    if(CreateDirectoryA(pathName, NULL))
    {
        memset(addressD, 0, strlen(addressD));
        strcpy(addressD, pathName);
        strcat(addressD, "\\");
        
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

OSAL_ReturnType OSAL_RemoveDirectory(char* name, char* path)
{
    char* directoryPath = makePath(path);
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    if (checkIfDirectoryExists(name, directoryPath) == OSAL_FAIL)
    {
        return OSAL_FAIL;
    }
    char pathName[OSAL_PATH_MAX_LENGHT] = "cd ";
    strcat(pathName, address);
    strcat(pathName, directoryPath);
    strcat(pathName, " && rmdir ");
    strcat(pathName, "/Q /S ");
    strcat(pathName, name);
    if(system(pathName) == 0)
    {
        memset(addressD,0,strlen(addressD));
        strcpy(addressD, address);
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

OSAL_ReturnType OSAL_OpenDirectory(char* name, char* path)
{
    char* directoryPath = makePath(path);
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    if (checkIfDirectoryExists(name, directoryPath) == OSAL_FAIL)
    {
        return OSAL_FAIL;
    }
    memset(addressD, 0, strlen(addressD));
    strcpy(addressD, address);
    strcat(addressD, directoryPath);
    strcat(addressD, "\\");
    strcat(addressD, name);
    strcat(addressD, "\\");
    return OSAL_OK;
}
