#include "filesystem.h"
#include <stdlib.h>
#include <string.h>
#include "OSALInit.h"

// TODO: koristiti camel case za nazive ovih funckija (fileNameValidation, accessValidation()...)
static int name_validation(char *name){
    if(strlen(name) == OSAL_File_name_min_lenght || strlen(name) > OSAL_File_name_max_lenght)
    // TODO: pratiti da po svim fajlovima stil uvlacenja bude isti, kao i '{', '}' zagrade. Nije mi toliko bitno koji stil je u pitanju, samo da bude konzistentno.
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

static int access_validation(char *access){
    if( !strcmp(access, "r") || !strcmp(access, "w") || !strcmp(access, "r/w"))
    {
        return OSAL_OK;
    }
    else 
    {
        return OSAL_FAIL;
    }
}

static int checkIfFileExists(char* fileName){
    char namep[OSAL_File_name_max_lenght];
    strcpy(namep, fileName);
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, addressD);
    strcat(command, " && IF EXIST ");
    strcat(command, namep);
    strcat(command, " EXIT 1");
    int var = system(command);
    if(var != OSAL_OK)
    {
        return OSAL_FAIL;
    }
    else
    {
        return OSAL_OK;
    }
}

static int checkIfDirectoryExists(char* directoryName, char* path){
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, address);
    strcat(command, path);
    strcat(command, " && IF EXIST ");
    strcat(command, directoryName);
    strcat(command, " EXIT 2");
    if(system(command) == OSAL_Directory_exists)
    {
        return OSAL_OK;
    }
    else
    {
        return OSAL_FAIL;
    }
}

// TODO: Deskriptivniji naziv funkcije, koji ce nam reci sta provjeravamo. Npr checkFileHandle
static int check(HANDLE* file)
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

// TODO: setFileAccess
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
    static char newPath[OSAL_address_max_length];
    char newc = '\\';
    char old = ' ';
    int i = 0, j = 0;
    newPath[j++] = newc;
    newPath[j++] = newc;

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
    newPath[j++] = newc;
    newPath[j++] = newc;
    newPath[j++] = '\0';
    return newPath;
}

HANDLE* OSAL_Create(char* name,char* access){
   // TODO: deskriptivniji naziv umjesto addressP
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
    if (checkIfFileExists(name) == OSAL_Test_PASS)
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
        NULL);
    if(check(File) == OSAL_OK)
    {
        return File;
    }
    else
    {
        return NULL;
    }
}

int OSAL_Console_File_Open(char* fileName){
    if (name_validation(fileName) != OSAL_Test_PASS)
    {
        return OSAL_FAIL;
    }
    
    if (checkIfFileExists(fileName) != OSAL_Test_PASS)
    {
        return OSAL_FAIL;
    }
    
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, addressD);
    strcat(command, " && ");
    strcat(command, fileName);
    // TODO: U ovom slucaju, ako je ok kad vrati 0, po mom misljenju je bolje staviti 'if(system(command) == 0)'
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
    {
        return OSAL_Test_FAIL;
    }
    
    if (checkIfFileExists(name) != OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
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
    if (checkIfFileExists(name) != OSAL_Test_PASS)
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
        NULL);
 
    if(check(File) == OSAL_Test_PASS)
    {
        return File;
    }
    else
    {
        return NULL;
    }  
}

int OSAL_Close(HANDLE* file)
{
    return CloseHandle(File);
}

int OSAL_Write(HANDLE* file, char* buffer)
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

int OSAL_Read(HANDLE* File, char* buffer, int numberOfBytesToRead, int position)
{
   if(position > numberOfBytesToRead)
   {
       return OSAL_Test_FAIL;
   }
   if(File == NULL)
   {
       return OSAL_Test_FAIL;
   }
   if(numberOfBytesToRead > GetFileSize(File, NULL))
   {
       return OSAL_Test_FAIL;
   }
   SetFilePointer(File, position, NULL, 0);
   DWORD dwBytesRead;
   ReadFile(File, buffer, numberOfBytesToRead - position, &dwBytesRead, NULL);
   buffer[i - position] = '\0';
}

int OSAL_Create_Directory(char* name, char* path)
{
    // TODO: bolji naziv za pathm smisliti
    char* pathm = make_path(path);
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
    
    if (checkIfDirectoryExists(name, pathm) == OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
   
    // TODO: ovo nije bas 'command', vise bi odgovarao 'pathName' naziv
    char command[OSAL_address_max_length];
    strcpy(command, addressD);
    strcat(command, pathm);
    strcat(command, name);
    if(CreateDirectoryA(command, NULL))
    {
        memset(addressD, 0, strlen(addressD));
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
    // TODO: bolji naziv za pathm smisliti
    char* pathm = make_path(path);
    if (name_validation(name) != OSAL_Test_PASS)
    {
        return OSAL_Test_FAIL;
    }
    if (checkIfDirectoryExists(name, pathm) == OSAL_Test_FAIL)
    {
        return OSAL_Test_FAIL;
    }
    char command[OSAL_address_max_length] = "cd ";
    strcat(command, address);
    strcat(command, pathm);
    strcat(command, " && rmdir ");
    strcat(command, "/Q /S ");
    strcat(command, name);

    if(!system(command)) // Razmotriti: if (system(command) == 0)
    {
        memset(addressD,0,strlen(addressD));
        strcpy(addressD, address);
            printf("aadres %s\n",addressD); // TODO: izbaciti na kraju
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
    if (checkIfDirectoryExists(name, pathm) == OSAL_Test_FAIL)
    {
        return OSAL_Test_FAIL;
    }
    memset(addressD, 0, strlen(addressD));
    strcpy(addressD, address);
    strcat(addressD, pathm);
    strcat(addressD, name);
    strcat(addressD, "\\");
    return OSAL_Test_PASS;
}
