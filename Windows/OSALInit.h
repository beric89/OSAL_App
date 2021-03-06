#ifndef OSAL_API_INIT_H 
#define OSAL_API_INIT_H

#define OSAL_APIINIT_VALUE_TRUE 1
#define OSAL_APIINIT_VALUE_FALSE -1
#define OSAL_APIINIT_ADDRESS "C:\\Temp\\"
#define OSAL_DIRECTORY_EXISTS 2
#define OSAL_PATH_MAX_LENGTH 200
#define OSAL_PRINTF_TEXT_MAX_LENGTH 200
#define OSAL_FILE_NAME_MIN_LENGHT 0
#define OSAL_FILE_NAME_MAX_LENGHT 200
#define OSAL_TRUE 1
#define OSAL_FALSE 0

typedef enum {
  OSAL_OK,
  OSAL_FAIL,
  OSAL_WRONG_ARGUMEN,
  OSAL_INVALID_OPERATION
} OSAL_ReturnType;

typedef enum {
    OSAL_CONSOLE_ENABLED,
    OSAL_CONSOLE_DISABLED
} OSAL_ConsoleEnableType;


OSAL_ConsoleEnableType consoleEnabled;
char address[OSAL_PATH_MAX_LENGTH];
char addressD[OSAL_PATH_MAX_LENGTH];
OSAL_ReturnType OSAL_APIInit (void);

#endif // OSAL_API_INIT_H

