#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "asembler.h"

typedef struct
{
    char symbol[MAX_INPUT];
    int address;
    char status[MAX_INPUT];
    char code [MAX_BITS];
} symbolLine;

symbolLine *sTable;

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
            if(!strcmp(getData(i,COMMAND),".data")||!strcmp(getData(i,COMMAND),".string"))
                strcpy(sTable[j].status,"data");

            else if (isEntry(temp))
                strcpy(sTable[j].status,"ent");

            else if (isExtern(temp))
                strcpy(sTable[j].status,"ext");
            j++;
        }
        addressCounter += codeLines(i);
        printf("%i\n",intToBase4(addressCounter));
    }

    for(i--; i>=j; i--)
    {
        free(sTable+i);
    }


    for(i=1; i<j; i++)
    {
        printf("%s\t%s\t%i\n",sTable[i].symbol,sTable[i].status,sTable[i].address);
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
    int counter=1;
    int j=0;
    int len;
    char operand1[MAX_INPUT];
    char operand2[MAX_INPUT];
    char command[MAX_INPUT];
    strcpy(operand1,getData(i,OPERAND1));
    strcpy(operand2,getData(i,OPERAND2));
    strcpy(command,getData(i,COMMAND));
    if(!strcmp(command,".data"))
    {
     len=strlen(operand2);
     for(j=0;j<len;j++)
     {
         if(isdigit(operand2[j]))
            counter++;
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
      int d[5];
      int j,i=0;
      while(num>0)
      {
           d[i] = (*num)%4;
           i++;
           num=(*num)/4;
      }
      for(j=i-1;j>=0;j--)
      {
            (*num) += (d[i])*(pow(10,j));
      }
 }
}
void freeSTable()
{
    free(sTable);
}
