#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "asembler.h"

typedef struct
{
    char label [31];
    char command [5];
    char operand1 [31];
    char operand2 [31];
     int address;
}metrixLine;

metrixLine *mat;

void metrixParam (FILE *file)
{
    char s;
    int state = LABEL;
    int lines = lineCounter(file);
    int addresCounter = 100;
    int i = 0;
    int j=0
    mat = malloc(sizeof(metrixLine) * lines);
    if (!mat)
    {
        printf("memory allocation failed");
        exit(0);
    }
    while (i<=lines)
    {
        s = fgetc(file);
        if (s!= '.')
        {
            while (s!= '\n' || s != EOF)
            {
                if(state = LABEL)
                {
                 if(j == 31 && s != ':')
                 {
                    printf("Memory crashed - the Label on line %i is more then 30 characters",i);
                    exit(0);
                 }
                 else if(s != ':')
                 {
                    if (j==0 && isalpha(s) == 0)
                    {
                        printf("First character on label in line %i is wrong", i);
                    }
                    if (isalpha(s)== 0 && isdigit(s)==0 && j !=0 )
                        printf("Wrong character on label in line %i", i);

                    mat.label[j] = s;
                    j++;

                 }
                 else
                    state = COMMAND;
                    j = 0;
                }
                else if (state = COMMAND)
                {
                    if ((j==31 && s != ' ')|| (j==5 && s != '\t'))
                    {
                        printf("Memory crashed - the Operand on line %i is more then 4 characters");
                        exit(0);
                    }
                    else if (j==0 && s != ' ')
                    {
                        mat.command[j] = s;
                        j++;
                    }
                    else if ((j>0 && s!=' ') || (j>0 && s!='\t'))
                    {
                        mat.command[j] = s;
                        j++
                    }
                    else if ((j>0 && s==' ') || (j>0 && s=='\t'))
                    {
                        state = OPERAND2;
                        j==0
                    }

                }
                else if (state = OPERAND1)
                {

                }
                else if (state = OPERAND2)
                {

                }
                s = fgetc(file);
            }

        }
        while (s != '\n')
        {
            s = fgetc(file);
        }
        i++;
    }



}


