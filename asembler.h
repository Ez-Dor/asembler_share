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
char* getParam(int index, int param);
void matrixParam(FILE *file);
int checkCommand (char com[]);
int checkAllCommands ();
