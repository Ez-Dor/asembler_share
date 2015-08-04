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
    char code [MAX_BITS];
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
    for(i=1,j=1; i<=line; i++)
    {

        strcpy(temp,getData(i,LABEL));
        if(strlen(temp))
        {
            strcpy(sTable[j].symbol,temp);
            sTable[j].address = addressCounter;
            intToBase4(&sTable[i].address);
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
    sTableLen=j;
}

char *getSymbolStatus(char symbol[])
{
    int i;
    for(i=0;i<sTableLen;i++)
    {
        if(!strcmp(symbol,sTable[i].symbol))
            return sTable[i].status;
    }
    return NULL;
}

void buildOutputTable()
{
    extern int line;
    int i,j;
/*The length of the output*/
    for(i=1,oTabelLen=0;i<=line;i++)
    {
        oTabelLen+=codeLines(i);
    }
/*Allocate memory for the output*/
     oTable = calloc(oTabelLen, sizeof(outputLine));
     if (!oTable)
    {
        printf("Memory allocation failed");
        exit(0);
    }
/*Insert code address to the table*/
    for(i=0;i<oTabelLen;i++)
    {
        oTable[i].address = i+FIRST_ADDRESS;
        intToBase4(&oTable[i].address);
    }
        for(i=0;i<oTabelLen;i++)
    {
        printf("%i\n",oTable[i].address);
    }
}
/*The method get line on input DB and return the "L" for IC*/
int lineIC(int i)
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
    /*the longest commend is a 5 characters*/
    strcpy(command,getData(i,COMMAND));
    if(!strcmp(command,".data") || !strcmp(command,".string"))
        return 0;

    while(!isdigit(command[j]))
        j++;

    if(command[j]=='2')
        counter = counter*2;

    return counter;
}

/*Run whole over the input DB and insert the right base 4 address address*/
void createAdress()
{
    extern int line;
    int len;
    int i=1;
    int j;
    int addressCounter = 100;
    for(j=0;i<=line;i++)
    {
        len = codeLines(i);


    }
}

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
    if(i<0 || i>line)
        return 0;
    if(!strcmp(command,".data"))
    {
     len=strlen(operand2);
     for(j=0;j<len;j++)
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
        len=strlen(operand1);
 /*the length minus the quotes*/
        return (counter+len-2);
    }
    else
    {

        if(strlen(operand1))
        {
            counter++;
            if(strlen(operand2)&& !(isRegister(operand1)&& isRegister(operand2)))
            {
                counter++;
            }

        }
        /*the longest commend is a 5 characters*/



        while(!isdigit(command[j]))
            j++;

        if(command[j]=='2')
            counter = (counter*2);

        return counter;
    }
}

void intToBase4 (int *num)
{
{
      int d[7];
      int i=0,j;
      double x=0;
      while((*num)>0)
      {
           d[i]=(*num)%4;
           i++;
           (*num)=(*num)/4;
      }
      for(x=0,j=i-1;j>=0;j--)
      {
        x += d[j]*pow(10,j);
      }
      (*num)=(int)x;
 }
}


void freeSTable()
{
    free(sTable);
}
