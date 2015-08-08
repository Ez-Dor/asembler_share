#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "asembler.h"

/*Struct for the symbol table every struct present a line*/
typedef struct
{
    char symbol[MAX_INPUT];
    int address;
    char status[MAX_INPUT];
} symbolLine;

/*Struct for the output table every struct present a line*/
typedef struct
{
    int address;
    unsigned int code;
} outputLine;

symbolLine *sTable;
outputLine *oTable;
int sTableLen,oTabelLen;

void buildSymbolTable()
{
    extern int line;
    char temp[MAX_INPUT];
    int i,j;
    int addressCounter = 100;
    sTable= calloc(line, sizeof(symbolLine));
    if (!sTable)
    {
        printf("Memory allocation failed");
        exit(0);
    }
    moveCulForOneOper();
    for(i=1,j=1; i<=line; i++)
    {
        strcpy(temp,getData(i,LABEL));
        if(strlen(temp))
        {
            strcpy(sTable[j].symbol,temp);
            sTable[j].address = addressCounter;
            if(!strcmp(getData(i,COMMAND),".data")||!strcmp(getData(i,COMMAND),".string"))
                strcpy(sTable[j].status,"data");

            else if (isEntry(temp))
                strcpy(sTable[j].status,"ent");

            else if (isExtern(temp))
                strcpy(sTable[j].status,"ext");
            j++;
        }

        addressCounter += codeLines(i);
    }

    for(i--; i>=j; i--)
    {
        free(sTable+i);
    }
    /*j should be the symbole table length*/
    sTableLen=j;
    /*address counter should be the length of the output*/
    oTabelLen = addressCounter-FIRST_ADDRESS;
}

int getSymbolAddress(char symbol[])
{
    int i;
    for(i=0; i<sTableLen; i++)
    {
        if(!strcmp(symbol,sTable[i].symbol))
            return sTable[i].address;
    }
    return 0;
}

void buildOutputTable()
{

    extern int line;
    extern char* fileName;
    int i=0,j=0,x=0,y=0,len=0,op1=0,op2=0,group=0, opcode=0,IC,DC,temp2=0;
    char temp1 [MAX_BITS];
    char operand1[MAX_INPUT];
    char operand2[MAX_INPUT];
    char command[MAX_INPUT];
    char oFile[FILENAME_MAX];
    FILE *fp;
    strcpy(oFile,fileName);
    strcat(oFile,".ob");


    /*Allocate memory for the output*/
    oTable = calloc(oTabelLen, sizeof(outputLine));
    if (!oTable)
    {
        printf("Memory allocation failed");
        exit(0);
    }
    /*Insert code address to the table*/
    for(i=0; i<oTabelLen; i++)
    {
        oTable[i].address = i+FIRST_ADDRESS;
    }



    /*insert the code*/
    for(i=1; i<=line; i++)
    {

        strcpy(operand1,getData(i,OPERAND1));
        strcpy(operand2,getData(i,OPERAND2));
        strcpy(command,getData(i,COMMAND));
        if(command[0]!='.')
        {
            /*Check the group*/
            if(strlen(getData(i,OPERAND2)))
            {
                if(strlen(getData(i,OPERAND1)))
                {
                    group = GROUP1;
                    if(!strcmp(command,"mov1")||!strcmp(command,"mov2"))
                        opcode=0;
                    else if(!strcmp(command,"cmp1")||!strcmp(command,"cmp2"))
                        opcode=1;
                    else if(!strcmp(command,"add1")||!strcmp(command,"add2"))
                        opcode=2;
                    else if(!strcmp(command,"sub1")||!strcmp(command,"sub2"))
                        opcode=3;
                    else if(!strcmp(command,"lea1")||!strcmp(command,"lea2"))
                        opcode=6;
                }
                else
                {
                    group = GROUP2;
                    if(!strcmp(command,"not1")||!strcmp(command,"not2"))
                        opcode=4;
                    else if(!strcmp(command,"clr1")||!strcmp(command,"clr2"))
                        opcode=5;
                    else if(!strcmp(command,"inc1")||!strcmp(command,"inc2"))
                        opcode=7;
                    else if(!strcmp(command,"dec1")||!strcmp(command,"dec2"))
                        opcode=8;
                    else if(!strcmp(command,"jmp1")||!strcmp(command,"jmp2"))
                        opcode=9;
                    else if(!strcmp(command,"bne1")||!strcmp(command,"bne2"))
                        opcode=10;
                    else if(!strcmp(command,"red1")||!strcmp(command,"red2"))
                        opcode=11;
                    else if(!strcmp(command,"prn1")||!strcmp(command,"prn2"))
                        opcode=12;
                    else if(!strcmp(command,"jsr1")||!strcmp(command,"jsr2"))
                        opcode=13;
                }
            }
            else
            {
                group = GROUP3;
                if(!strcmp(command,"rts1")||!strcmp(command,"rts2"))
                    opcode=14;
                else if(!strcmp(command,"stop1")||!strcmp(command,"stop2"))
                    opcode=15;

            }
            /*present status for operands*/
            /*operand1*/
            op1=IS_EMPTY;
            if(group==GROUP1 && isNumeric(operand1,i) )
                op1=IS_NUMERIC;
            else if (group==GROUP1 && isLabel(operand1))
                op1=IS_LABEL;
            else if(group==GROUP1 && isRegister(operand1))
                op1=IS_REGISTER;

            /*operand2*/
            op2=IS_EMPTY;
            if(group!=GROUP3 && isNumeric(operand2,i))
                op2=IS_NUMERIC;
            else if (group!=GROUP3 && isLabel(operand2))
                op2=IS_LABEL;
            else if(group!=GROUP3 && isRegister(operand2))
                op2=IS_REGISTER;

            len=codeLines(i);

            if(isDoubleCommend(command))
            {
                len = len/2;
            }


            for(j=0; j<len; x++,j++)
            {

                if(j==0)
                {

                    temp2=group;
                    temp2<<=4;
                    temp2+=opcode;
                    temp2<<=2;
                    temp2+=op1;
                    temp2<<=2;
                    temp2+=op2;
                    temp2<<=2;
                    oTable[x].code = temp2;
                }

                else if(group == GROUP1 && j>0)
                {
                    printf("%s,%s\n",command,operand2);
                    if(op1==IS_REGISTER && op2==IS_REGISTER)
                    {
                        temp2=atoi(&operand1[1]);
                        temp2<<=5;
                        temp2+=atoi(&operand2[1]);
                        temp2<<=2;
                        oTable[x].code = temp2;

                    }
                    else if(j==1)
                    {
                        if(op1==IS_REGISTER)
                        {
                            temp2 = atoi(&operand1[1]);
                            temp2 <<=7;
                            oTable[x].code =temp2;
                        }
                        else if(op1==IS_NUMERIC)
                        {
                            temp2 = atoi(&operand1[1]);
                            if(temp2<0)
                                isNegative(&temp2);

                            oTable[x].code =(unsigned int)temp2;
                            oTable[x].code <<=2;


                        }
                        else if(op1==IS_LABEL)
                        {
                            oTable[x].code = getSymbolAddress(operand1);
                            oTable[x].code <<=2;
                            oTable[x].code++;
                            if(!isExtern(operand1))
                                oTable[x].code++;
                        }
                    }
                    else if(j==2)
                    {
                        if(op2==IS_REGISTER)
                        {

                            oTable[x].code = atoi(&operand2[1]);
                            oTable[x].code <<=2;
                        }
                        else if(op2==IS_NUMERIC)
                        {

                            temp2 = atoi(&operand2[1]);
                            if(temp2<0)
                                isNegative(&temp2);

                            oTable[x].code =(unsigned int)temp2;
                            oTable[x].code <<=2;
                        }
                        else if(op2==IS_LABEL)
                        {
                            oTable[x].code = getSymbolAddress(operand2);
                            oTable[x].code <<=2;
                            oTable[x].code++;
                            if(!isExtern(operand2))
                                oTable[x].code++;
                        }
                    }
                }

                else if(group == GROUP2 && j>0)
                {
                    if(op2==IS_REGISTER)
                    {

                        oTable[x].code = atoi(&operand2[1]);
                        oTable[x].code <<=2;
                    }
                    if(op2==IS_NUMERIC)
                    {
                        temp2 = atoi(&operand2[1]);
                            if(temp2<0)
                                isNegative(&temp2);

                            oTable[x].code =(unsigned int)temp2;
                            oTable[x].code <<=2;
                    }

                    if(op2==IS_LABEL)
                    {
                        oTable[x].code = getSymbolAddress(operand2);
                        oTable[x].code <<=2;
                        oTable[x].code++;
                        if(!isExtern(operand2))
                            oTable[x].code++;
                    }

                }
            }

            if(isDoubleCommend(command))
            {
                for(j=0; j<len; x++,j++)
                {
                    oTable[x].code=oTable[x-len].code;
                }
            }

        }
    }
    IC = oTabelLen-x;
    DC = x;
    intToBase4(&DC);
    intToBase4(&IC);
    for(i=1;i<=line;i++)
    {
        strcpy(command,getData(i,COMMAND));
         if(command[0]=='.')
         {
            strcpy(operand1,getData(i,OPERAND1));
            strcpy(operand2,getData(i,OPERAND2));
            len = codeLines(i);
            for(y=0,j=0;j<len;j++,x++)
            {
                if(!strcmp(command,".string"))
                {
                    if(j<len-1)
                        oTable[x].code = operand2[j+1];
                    else
                        oTable[x].code = 0;
                }
                else if(!strcmp(command,".data"))
                {
                    if(j==0)
                    {
                        temp2 = atoi(operand1);
                        if(temp2<0)
                            isNegativeOn12Bits(&temp2);
                        oTable[x].code =(unsigned int) temp2;
                    }
                    else
                    {
                        temp2 = atoi(&operand2[y]);
                        if(temp2<0)
                            isNegativeOn12Bits(&temp2);
                        oTable[x].code =(unsigned int) temp2;
                        do
                        {
                            y++;
                        }while(y<MAX_INPUT && operand2[y]!=',' && operand2[y]!='\0' );

                        if(operand2[y]==',')
                            y++;

                    }

                }
            }

         }
    }
    fp = fopen(oFile,"w+");
    fprintf(fp,"\t%i %i",DC,IC);
    fputc('\n',fp);
    for(i=0; i<oTabelLen; i++)
    {
        intToBase4(&oTable[i].address);
        intToBase4(&oTable[i].code);
        fprintf(fp,"%i\t%06u\n",oTable[i].address,oTable[i].code);
    }
    fclose(fp);

}



/*The method get line on input DB and return the "L" for IC*/
/*int lineIC(int i)
{
    int counter=1;
    int j=0;
    char operand1[MAX_INPUT];
    char operand2[MAX_INPUT];
    char command[MAX_INPUT];
    strcpy(operand1,getData(i,OPERAND1));
    strcpy(operand2,getData(i,OPERAND2));
    strcpy(command,getData(i,COMMAND));
    if(strlen(operand1))
    {
        counter++;
        if(strlen(operand2)&& !(isRegister(operand1)&& isRegister(operand2)))
        {
            counter++;
        }

    }

    strcpy(command,getData(i,COMMAND));
    if(!strcmp(command,".data") || !strcmp(command,".string"))
        return 0;

    while(!isdigit(command[j]))
        j++;

    if(command[j]=='2')
        counter = counter*2;

    return counter;
}*/



/*The method get line on input DB and return how many code lines have on the line*/
int codeLines(int i)
{
    extern int line;
    int counter=1;
    int j=0;
    int len;
    char operand1[MAX_INPUT];
    char operand2[MAX_INPUT];
    char command[MAX_INPUT];
    strcpy(operand1,getData(i,OPERAND1));
    strcpy(operand2,getData(i,OPERAND2));
    strcpy(command,getData(i,COMMAND));
    if(i<1 || i>line)
        return 0;
    if(!strcmp(command,".data"))
    {
        len=strlen(operand2);
        for(j=0; j<len; j++)
        {
            if(isdigit(operand2[j]))
            {
                counter++;
                while(isdigit(operand2[j])&&j<len)
                    j++;
            }
        }
        return counter;
    }
    else if(!strcmp(command,".string"))
    {
        len=strlen(operand2);
        /*the length minus the quotes*/
        return (counter+len-2);
    }
    else
    {

        if(strlen(operand2))
        {
            counter++;
            if(strlen(operand1)&& !(isRegister(operand1)&& isRegister(operand2)))
            {
                counter++;
            }

        }

        if(isDoubleCommend(command))
            counter = (counter*2);

        return counter;
    }
}

int isDoubleCommend (char command[])
{
    int j=0;
    while(!isdigit(command[j]))
        j++;

    if(command[j]=='2')
        return TRUE;

    return FALSE;
}

/*The function change the value of the intiger to base 4*/
void intToBase4 (unsigned int *num)
{
    int d[7];
    int j,i=0;
    double x=0;
    while((*num)>0)
    {
        d[i]=(*num)%4;
        i++;
        (*num)=(*num)/4;
    }
    for(x=0,j=i-1; j>=0; j--)
    {
        x += d[j]*pow(10,j);
    }
    (*num)=(unsigned int)x;

}

void isNegative (unsigned int *num)
{
    unsigned int temp;
    int i,j;
    int bits[10];
    double x;
    temp = *num;
    *num=0;
    j=1;
    for(i=0; i<10; i++)
    {
        bits[i] = (temp&j);
        temp>>=1;
    }

    for(x=0,i=0; i<10; i++)
    {
        x+= bits[i]*(pow(2,i));
    }

    *num=(unsigned int)x;
}

void isNegativeOn12Bits (unsigned int *num)
{
    unsigned int temp;
    int i,j;
    int bits[MAX_BITS-1];
    double x;
    temp = *num;
    *num=0;
    j=1;
    for(i=0; i<MAX_BITS-1; i++)
    {
        bits[i] = (temp&j);
        temp>>=1;
    }

    for(x=0,i=0; i<MAX_BITS-1; i++)
    {
        x+= bits[i]*(pow(2,i));
    }

    *num=(unsigned int)x;
}


void freeTables()
{
    free(sTable);
    free(oTable);
}
