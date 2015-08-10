/*Constants for database struct*/
#ifndef ASEMBLER_H_
#define ASEMBLER_H_
#endif

#define INPUTLINE 0

#define LABEL 1
#define COMMAND 2
#define OPERAND1 3
#define OPERAND2 4

#define MAX_INPUT 31
#define FIRST_ADDRESS 100

/*Command groups*/
#define GROUP1 2
#define GROUP2 1
#define GROUP3 0

#define FIRST_LINE 0
#define SECOND_LINE 1
#define THIRD_LINE 2

/*Operands binary values*/
#define IS_NUMERIC 0
#define IS_LABEL 1
#define IS_REGISTER 3
#define IS_EMPTY 0

/*Bits*/
#define ONE_BIT 1
#define TWO_BITS 2
#define FOUR_BITS 4
#define FIVE_BITS 5
#define TEN_BITS 10
#define MAX_BITS 13

/*Constants for Boolean*/
#define TRUE 1
#define FALSE 0

/*Direct Addressing Min and Max values*/
#define DIRECTMIN -512
#define DIRECTMAX 511

/*.Data lines min and max values*/
#define MINDATANUM -2048
#define MAXDATANUM 2047

#define COMMA 0
#define NUMBER 1


/*Function prototype*/

    /*inputDB function*/
int lineCounter(FILE *file);
void printLine(int i);
void printMatrix();
char* getData(int index, int param);
void freeMatrixMem();
int getInputLine(int i);
void setData (int index, int param,char data []);

/*Validation function*/
int buildMatrix(FILE *file);
int checkCommand (char com[], int i);
int checkAllCommands ();
int checkLabels ();
int isLabel(char operand[]);
int isNumeric(char operand[], int i);
int isRegister(char oper[]);
int isData(int i);
int isString(int i);
int changeDollars();
int isExtern(char param[]);
int isEntry(char param[]);

/*Parser function*/
void buildSymbolTable();
void freeTables();
void buildOutputTable();
void moveCulForOneOper();
void isNegativeOn12Bits (unsigned int *num);
void isNegative (unsigned int *num);
void intToBase4 (unsigned int *num);
int isDoubleCommend (char command[]);
int getSymbolAddress(char symbol[]);
int codeLines(int i);


