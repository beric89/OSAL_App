#include "filesystem.h"
#include <stdlib.h>
#include <string.h>

static OSAL_ReturnType nameValidation(char *name){
    if(strlen(name) == OSAL_FILE_NAME_MIN_LENGTH || strlen(name) > OSAL_FILE_NAME_MAX_LENGTH)
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

static OSAL_ReturnType checkFileHandle(HANDLE* file)
{
    if(file == INVALID_HANDLE_VALUE)
    {
        return OSAL_FAIL;
    }
    else if (file == ERROR_FILE_EXISTS)
    {
        return OSAL_FAIL;
    }
    else if (file == ERROR_FILE_NOT_FOUND )
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

static char* makePath(char* filePath, char* name)
{
    static char path[OSAL_PATH_MAX_LENGTH];
    strcpy(path, OSAL_APIINIT_ADDRESS);
    strcat(path, "\\");
    strcat(path, filePath);
    strcat(path, name);
    return path;
}

// Handling case when spaces are present in a path.
static char* convertPath(char* path)
{
    if(strcmp(path, ""))
    {
        static char newPath[OSAL_PATH_MAX_LENGTH];
        char newc = '\\';
        int i = 0, j = 0;
        char old = ' ';
        while(path[i]!='\0')
        {
            if(path[i] == old)
            {
                newPath[j++] = newc;
            }
            else
            {
                newPath[j++] = path[i];
            }
            i++;
        }
        newPath[j++] = newc;
        newPath[j++] = '\0';
        return newPath;
    }
    return "";
}

static int checkIfFileExists(char* filePath, char* name){
    char filePathExists[OSAL_PATH_MAX_LENGTH];
    strcpy(filePathExists, "cd ");
    strcat(filePathExists, OSAL_APIINIT_ADDRESS);
    strcat(filePathExists, "\\");
    strcat(filePathExists, filePath);
    strcat(filePathExists, " && IF EXIST ");
    strcat(filePathExists, name);
    strcat(filePathExists, " EXIT 2");
    if(system(filePathExists) == 2)
    {
        return OSAL_TRUE;
    }
    else
    {
        return OSAL_FALSE;
    }
}

HANDLE* OSAL_Create(char* filePath, char* name, char* access){
    char* fileConvertPath;
    fileConvertPath = convertPath(filePath);
    fileConvertPath = makePath(fileConvertPath, name);
    if (nameValidation(name) == OSAL_FAIL)
    {
        return NULL;
    }
    if (accessValidation(access) == OSAL_FAIL)
    {
        return NULL;
    }
    DWORD generic;
    DWORD fileShareWrite = setFileAccess(access, &generic);
    HANDLE file = CreateFile(
        fileConvertPath,
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

OSAL_ReturnType OSAL_ConsoleFileOpen(char* filePath, char* name){
    char* fileConvertPath = convertPath(filePath);
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    if (checkIfFileExists(fileConvertPath, name) == OSAL_FALSE)
    {
        return OSAL_FAIL;
    }
    char filePathOpen[OSAL_PATH_MAX_LENGTH];
    strcpy(filePathOpen, "cd ");
    strcat(filePathOpen, OSAL_APIINIT_ADDRESS);
    strcat(filePathOpen, "\\");
    strcat(filePathOpen, fileConvertPath);
    strcat(filePathOpen, " && ");
    strcat(filePathOpen, name);
    printf("%s\n", filePathOpen);
    if((system(filePathOpen) == 0))
    {
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

OSAL_ReturnType OSAL_Remove(char* filePath, char* name){
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    char* fileConvertPath;
    fileConvertPath = convertPath(filePath);
    fileConvertPath = makePath(fileConvertPath, name);
    int returnValueRemove = DeleteFileA(fileConvertPath);
    if(returnValueRemove == 0)
    {
        return OSAL_FAIL;
    }
    else if (returnValueRemove == ERROR_FILE_NOT_FOUND)
    {
        return OSAL_FAIL;
    }
    else if (returnValueRemove == ERROR_ACCESS_DENIED)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

HANDLE* OSAL_Open(char* filePath, char* name, char* access)
{
    if (nameValidation(name) != OSAL_OK)
    {
        return NULL;
    }
    if (accessValidation(access) == OSAL_FAIL)
    {
        return NULL;
    }
    char* fileConvertPath;
    fileConvertPath = convertPath(filePath);
    fileConvertPath = makePath(fileConvertPath, name);

    DWORD generic;
    DWORD fileShareWrite = setFileAccess(access, &generic);

    HANDLE file = CreateFile(
        fileConvertPath,
        generic,
        fileShareWrite,
        NULL,
        OPEN_EXISTING,
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

OSAL_ReturnType OSAL_CreateDirectory(char* directoryPath, char* name)
{
    char* directoryPathconvert = convertPath(directoryPath);
    directoryPathconvert = makePath(directoryPathconvert, name);
    if (nameValidation(name) != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    int resultCreateDirectory = CreateDirectoryA(directoryPathconvert, NULL);
    if(resultCreateDirectory == 0)
    {
        return OSAL_FAIL;
    }
    else if (resultCreateDirectory == ERROR_ALREADY_EXISTS)
    {
        return OSAL_FAIL;
    }
    else if (resultCreateDirectory == ERROR_PATH_NOT_FOUND)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

OSAL_ReturnType OSAL_RemoveDirectory(char* path, char* name)
{
    char* directoryPathconvert = convertPath(path);
    if (nameValidation(name) == OSAL_FAIL)
    {
        return OSAL_FAIL;
    }
    if (checkIfFileExists(directoryPathconvert, name) == OSAL_FALSE)
    {
        return OSAL_FAIL;
    }
    char removePath[OSAL_PATH_MAX_LENGTH] = "cd ";
    strcat(removePath, OSAL_APIINIT_ADDRESS);
    strcat(removePath, "\\");
    strcat(removePath, directoryPathconvert);
    strcat(removePath, " && rmdir ");
    strcat(removePath, "/Q /S ");
    strcat(removePath, name);
    if(system(removePath) == 0)
    {
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

