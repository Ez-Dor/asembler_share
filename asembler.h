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
int lineCounter(FILE *file);
void printLine(int i);
void printMatrix();
char* getData(int index, int param);
void freeMatrixMem();
int buildMatrix(FILE *file);
int checkCommand (char com[], int i);
int checkAllCommands ();
int checkLabels ();
int getInputLine(int i);
int isLabel(char operand[]);
int isNumeric(char operand[], int i);
int isRegister(char oper[]);
int isData(int i);
int isString(int i);
void setData (int index, int param,char data []);
int changeDollars();
int strlenWithoutSpace(char c[]);

/*
int checkOperand1 (char com[], int i);
void moveCulForOneOper();*/
