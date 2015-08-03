#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "asembler.h"

typedef struct
{
    char symbol[MAX_INPUT];
    int adress;
    char status[MAX_INPUT];
    char code [MAX_BITS];
}symbolLine;

void buildSymbolTable()
{
    extern char* fileName;
    extern int line;
    char temp[MAX_INPUT];
    int i;
    char fileExt[FILENAME_MAX];
    char fileEnt[FILENAME_MAX];
    int existExt =TRUE;
    int existEnt =TRUE;
    strcpy(fileExt,fileName);
    strcat(fileExt,".ext");
    FILE *fpx = fopen(fileExt,"r");
    if(!fileExt)
        existExt = FALSE;
    strcpy(fileEnt,fileName);
    strcat(fileEnt,".ent");
    FILE *fpn = fopen(fileEnt,"r");
    if(!fileEnt)
        existEnt = FALSE;

    symboline *sTable = calloc(line, sizeof(symbolLine));
    if (!sTable)
    {
        printf("Memory allocation failed");
        exit(0);
    }
     for(i=1;i<=line;i++)
     {

     }
}
