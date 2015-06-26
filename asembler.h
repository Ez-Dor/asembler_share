#define INPUTLINE 0
#define LABEL 1
#define COMMAND 2
#define OPERAND1 3
#define OPERAND2 4
#define MAX_INPUT 31
#define TRUE 1
#define FALSE 0

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
int isLabel(char operand[], int param);
int checkOperand1 (char com[], int i);
int isRegister(char oper[]);
void setData (int index, int param,char data []);
