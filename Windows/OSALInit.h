#define OSAL_APIInit_value_TRUE 1
#define OSAL_APIInit_value_FALSE -1
#define OSAL_APIInit_address "C:\\Temp\\"
#define OSAL_File_name "test.txt"
#define OSAL_Diretory_name "TESTtest"
#define OSAL_Printf_string "test test test"
#define OSAL_Test_PASS 1
#define OSAL_Test_FAIL 0
#define OSAL_address_max_length 200
#define OSAL_printf_text_max_lenght 200
#define OSAL_File_name_min_lenght 0
#define OSAL_File_name_max_lenght 10
#define OSAL_Read_position_correct 5
#define OSAL_Read_position_worse 50
#define OSAL_READ_TEXT_CORRECT "TEST TEST TEST TEST!"
#define OSAL_Write_text "Test test test test!"
#define OSAL_Directory_exists 2

int en_dis;
char address[OSAL_address_max_length];
char addressD[OSAL_address_max_length];
int OSAL_APIInit (void);

