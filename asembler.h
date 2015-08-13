/*Include guard*/
#ifndef ASEMBLER_H_
#define ASEMBLER_H_
#endif

/*should present status*/
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

/*For every code line have between 1-3 different code lines */
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

/*input collection function*/
/*Read line by line in the input and sort the data into a struct*/
int buildMatrix(FILE *file);
/*Count data lines in the input file*/
int lineCounter(FILE *file);
/*Print a line from the matrix after the input was sorted*/
void printLine(int i);
/*Print all the lines after the input was sorted*/
void printMatrix();
/*Get a specific value in line index, parameter should be between 0-4, see constants for values*/
char* getData(int index, int param);
/*Free matrix memory*/
void freeMatrixMem();
/*Get the line number in the input file [not ignoring ext/ent lines like the matrix does]*/
int getInputLine(int i);
/*Change a specific value in the matrix*/
void setData (int index, int param,char data []);

/*Validation function*/
/*Validates a single line's command and operands*/
int checkCommand (char com[], int i);
/*Checks all commands and operands*/
int checkAllCommands ();
/*Checks for duplicate labels*/
int checkLabels ();
/*Checks if the operand is a legal label*/
int isLabel(char operand[]);
/*Checks that the numeric value is valid, must begin with # and follows by a signed number*/
int isNumeric(char operand[], int i);
/*Checks the the value is a legal register*/
int isRegister(char oper[]);
/*Checks the legality of .data numeric values*/
int isData(int i);
/*Checks that a string is legal, can't be longer than 31 chars*/
int isString(int i);
/*Swap all $$ operands with the last operand used and check for legality*/
int changeDollars();
/*Is the data in the external file?*/
int isExtern(char param[]);
/*Is the data in the entry file?*/
int isEntry(char param[]);

/*Parser function*/
/*Build the symbol table*/
void buildSymbolTable();
/*Free table memory*/
void freeTables();
/*Build the Output data table into a struct*/
void buildOutputTable();
/*Move all the single operand command from the source column to the destination column for easy parsing*/
void moveColForOneOper();
/*Check if the nubmer is Negative on 12 bits*/
void isNegativeOn12Bits (unsigned int *num);
/*Checks negative in decimal*/
void isNegative (unsigned int *num);
/*Change to base 4*/
void intToBase4 (unsigned int *num);
/*Copy the last command*/
int isDoubleCommend (char command[]);
/*Get the symbol address*/
int getSymbolAddress(char symbol[]);
/*Get the code lines*/
int codeLines(int i);


