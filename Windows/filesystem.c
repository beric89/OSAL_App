#include "filesystem.h"
#include <stdlib.h>
#include <string.h>
#include "OSALInit.h"

static int name_validation(char *name){
    if(strlen(name) == OSAL_File_name_min_lenght || strlen(name) > OSAL_File_name_max_lenght)
        return OSAL_Test_FAIL;
    else
        return OSAL_Test_PASS;
}

static int access_validation(char *access){
    if( !strcmp(access, "r") || !strcmp(access, "w") || !strcmp(access, "r/w"))
        return OSAL_Test_PASS;
    else 
        return OSAL_Test_FAIL;
}

static int check_if_exists(char* name){
    char namep[OSAL_File_name_max_lenght];
    strcpy(namep, name);
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, addressD);
    strcat(command, " && IF EXIST ");
    strcat(command, namep);
    strcat(command, " EXIT 1");
    int var = system(command);
    if(var != OSAL_Test_PASS)
        return OSAL_Test_FAIL;
    else 
        return OSAL_Test_PASS;
}

static int check_if_exists_directory(char* name, char* path){
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, address);
    strcat(command, path);
    strcat(command, " && IF EXIST ");
    strcat(command, name);
    strcat(command, " EXIT 2");
    int var = system(command);
    if(var == OSAL_Directory_exists)
        return OSAL_Test_PASS;
    else 
        return OSAL_Test_FAIL;
}

static int check(HANDLE* File)
{
    if(File == INVALID_HANDLE_VALUE)
    {
        return OSAL_Test_FAIL;
    }
    else
    {
        return OSAL_Test_PASS;
    }
}

static DWORD set_access(char* access, DWORD* generic)
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

static void make_address(char* addressP, char* name)
{
    strcpy(addressP, addressD);
    strcat(addressP, name);
}

static char* make_path(char* path)
{
    static char new[OSAL_address_max_length];
    char newc = '\\';
    char old = ' ';
    int i = 0, j = 0;
    new[j++] = newc;
    new[j++] = newc;

    while(path[i]!='\0')
    {
        if(path[i] == old)
        {
            new[j++] = newc;
            new[j++] = newc;
        }
        else
        {
            new[j++] = path[i];   
        }
        i++;
    }
    new[j++] = newc;
    new[j++] = newc;
    new[j++] = '\0';
    return new;
}

HANDLE* OSAL_Create(char* name,char* access){
   
    char addressP[OSAL_address_max_length];
    make_address(addressP, name);
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return NULL;
    }
    if (access_validation(access) != OSAL_Test_PASS)
    {
        return NULL;
    }
    if (check_if_exists(name) == OSAL_Test_PASS)
    {
        return NULL;
    }
    DWORD generic;
    DWORD fileShareWrite = set_access(access, &generic);  
    HANDLE File = CreateFile(
        addressP,
        generic,
        fileShareWrite, 
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    if(check(File) == OSAL_Test_PASS)
    {
        return File;
    }
    else
    {
        return NULL;
    }
}

int OSAL_Console_File_Open(char* name){
    if (name_validation(name) != OSAL_Test_PASS)
        return OSAL_Test_FAIL;
    
    if (check_if_exists(name) != OSAL_Test_PASS)
        return OSAL_Test_FAIL;
    
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, addressD);
    strcat(command, " && ");
    strcat(command, name);
    if(!system(command))
    {
        return OSAL_Test_PASS;
    }
    else
    {
        return OSAL_Test_FAIL;
    }
}

int OSAL_Remove(char* name){
    if (name_validation(name) != OSAL_Test_PASS)
        return OSAL_Test_FAIL;
    
    if (check_if_exists(name) != OSAL_Test_PASS)
        return OSAL_Test_FAIL;

    char file[OSAL_address_max_length];
    strcpy(file, addressD);
    strcat(file, name);
    return DeleteFileA(file);
}

HANDLE* OSAL_Open(char* name, char* access)
{
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return NULL;
    }
    if (access_validation(access) != OSAL_Test_PASS)
    {
        return NULL;
    }
    if (check_if_exists(name) != OSAL_Test_PASS)
    {
        return NULL;
    }
   
    char addressP[OSAL_address_max_length];
    make_address(addressP, name);
    
    DWORD generic;
    DWORD fileShareWrite = set_access(access, &generic);    
 
    HANDLE File = CreateFile(
        addressP,
        generic,
        fileShareWrite, 
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
 
    if(check(File) == OSAL_Test_PASS)
    {
        return File;
    }
    else
    {
        return NULL;
    }  
}

int OSAL_Close(HANDLE* File)
{
    return CloseHandle(File);
}

int OSAL_Write(HANDLE* File, char* buffer)
{
    if (strlen(buffer) == OSAL_Test_FAIL)
    {
        return OSAL_Test_FAIL;
    }
    
    DWORD dwBytesToWrite = (DWORD)strlen(buffer);
    DWORD dwBytesWritten = 0;
    
    int result = WriteFile(
                    File,
                    buffer,
                    dwBytesToWrite,
                    &dwBytesWritten,
                    NULL);

    if (result == OSAL_Test_FAIL)
    {
        return OSAL_Test_FAIL;
    }
    else
    {
        if (dwBytesWritten != dwBytesToWrite)
        {
            return OSAL_Test_FAIL;
        }
        else
        {
            return OSAL_Test_PASS;
        }
    }
}

int OSAL_Read(HANDLE* File,char* buffer, int i, int position)
{
   if(position > i)
   {
       return OSAL_Test_FAIL;
   }
   if(File == NULL)
   {
       return OSAL_Test_FAIL;
   }
   if(i > GetFileSize(File, NULL))
   {
       return OSAL_Test_FAIL;
   }
   SetFilePointer(File, position, NULL, 0);
   DWORD dwBytesRead;
   ReadFile(File, buffer, i-position,&dwBytesRead, NULL);
   buffer[i-position] = '\0';
}

int OSAL_Create_Directory(char* name, char* path)
{
    char* pathm = make_path(path);
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
    
    if (check_if_exists_directory(name, pathm) == OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
   
    char command[OSAL_address_max_length];
    strcpy(command, addressD);
    strcat(command, pathm);
    strcat(command, name);
    if(CreateDirectoryA(command, NULL))
    {
        memset(addressD,0,strlen(addressD));
        strcpy(addressD, command);
        strcat(addressD, "\\");
        
        return OSAL_Test_PASS;
    }
    else
    {
        return OSAL_Test_FAIL;
    }
}

int OSAL_Remove_Directory(char* name, char* path)
{
    char* pathm = make_path(path);
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
    if (check_if_exists_directory(name, pathm) == OSAL_Test_FAIL)
    {
        return OSAL_Test_FAIL;
    }
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, address);
    strcat(command, pathm);
    strcat(command, " && rmdir ");
    strcat(command, "/Q /S ");
    strcat(command, name);
    if(!system(command))
    {
        memset(addressD,0,strlen(addressD));
        strcpy(addressD, address);
            printf("aadres %s\n",addressD);
        return OSAL_Test_PASS;
    }
    else
    {
        return OSAL_Test_FAIL;
    }
}

int OSAL_Open_Directory(char* name, char* path)
{
    char* pathm = make_path(path);
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
    if (check_if_exists_directory(name, pathm) == OSAL_Test_FAIL)
    {
        return OSAL_Test_FAIL;
    }
    memset(addressD,0,strlen(addressD));
    strcpy(addressD, address);
    strcat(addressD, pathm);
    strcat(addressD, name);
    strcat(addressD, "\\");
    return OSAL_Test_PASS;
}
