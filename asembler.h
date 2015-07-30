#define INPUTLINE 0
#define LABEL 1
#define COMMAND 2
#define OPERAND1 3
#define OPERAND2 4
#define MAX_INPUT 31
#define TRUE 1
#define FALSE 0

/*typedef struct
{
    *char mov1 = "mov1";
    *char mov2 = "mov2";
    *char cmp1 = "cmp1";
    *char cmp2 = "cmp2";
    *char add1 = "add1";
    *char add2 = "add2";
    *char sub1 = "sub1";
    *char sub2 = "sub2";
    *char _not1 = "not1";
    *char _not2 = "not2";
    *char clr1 = "clr1";
    *char clr2 = "clr2";
    *char lea1 = "lea1";
    *char lea2 = "lea2";
    *char inc1 = "inc1";
    *char inc2 = "inc2";
    *char dec1 = "dec1";
    *char dec2 = "dec2";
    *char jmp1 = "jmp1";
    *char jmp2 = "jmp2";
    *char bne1 = "bne1";
    *char bne2 = "bne2";
    *char red1 = "red1";
    *char red2 = "red2";
    *char prn1 = "prn1";
    *char prn2 = "prn2";
    *char jsr1 = "jsr1";
    *char jsr2 = "jsr2";
    *char rts1 = "rts1";
    *char rts2 = "rts2";
    *char stop1 = "stop1";
    *char stop2 = "stop2";
}*/
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
void moveCulForOneOper();
int changeDollars();
int strlenWithoutSpace(char c[]);
