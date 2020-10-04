// TODO: Obicno je praksa da se defineovi pisu u CAPS LOCK-u (npr. OSAL_ADDRESS_MAX_LENGTH). Preimenovati.
#define OSAL_APIInit_value_TRUE 1
#define OSAL_APIInit_value_FALSE -1
// TODO za Milana: Razmotriti da li ce ovo biti forma putanje ili  C:\Temp\? (a da imamo staticku funkciju koja ce transformisati u \\ oblik)
#define OSAL_APIInit_address "C:\\Temp\\"

// TODO: sve definove koji se odnose na testove treba izmjestiti iz implementacijskih c i h fajlova. Ne bi smjela rijec test da se koristi unutar Windows foldera.
// Premjestiti ih u odgovarajuce test fajlove
#define OSAL_File_name "test.txt"
#define OSAL_Diretory_name "TESTtest"
#define OSAL_Printf_string "test test test"

//TODO: Za povratne vrijednosti se obicno koristi enum, koji bi objedinio sve moguce povratne vrijednosti npr:
// typedef enum {
//  OSAL_OK,
//  OSAL_FAIL,
//  OSAL_WRONG_ARGUMENT,
//  OSAL_INVALID_OPERATION
//} OSAL_ReturnType;
// Onda bi u kodu, funkcije bile deklarisane kao "OSAL_ReturnType OSAL_APIInit (void)", sto se svodi na isto kao i kad je "int OSAL_APIInit (void)", ali je kompaktnije rjesenje, manje podlozno greskama, lakse za dokumentovanje..
// Takodje za:
// // typedef enum {
//  OSAL_CONSOLE_ENABLED,
//  OSAL_CONSOLE_DISABLED,
//} OSAL_ConsoleEnableType;
#define OSAL_Test_PASS 1
#define OSAL_Test_FAIL 0
// TODO: koristiti izraz 'path' umjesto 'address' da se izbjegne konfuzija sa memorijskim adresama.
#define OSAL_address_max_length 200
#define OSAL_PRINTF_TEXT_MAX_LENGTH 200
#define OSAL_File_name_min_lenght 0
// TODO: 10 nije dovoljno za max duzinu naziva fajla. Povecati
#define OSAL_File_name_max_lenght 10
#define OSAL_Read_position_correct 5
#define OSAL_Read_position_worse 50
#define OSAL_Read_text_correct "TEST TEST TEST TEST!"
#define OSAL_Write_text "Test test test test!"
#define OSAL_Directory_exists 2

//TODO: potrebno je koristiti deskriptivnije nazive za varijable, pogotovo globalne. Nije bas jasno iz naziva sta oznacavaju varijable ispod...
// npr consoleEnabled;
//Takodje, nije mi i dalje jasan koncept oko address i addressD.
OSAL_ConsoleEnableType consoleEnabled;
char address[OSAL_address_max_length];
char addressD[OSAL_address_max_length];
int OSAL_APIInit (void);

