#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "asembler.h"

typedef struct
{
    char label [31];
    char command [31];
    char operand1 [31];
    char operand2 [31];
     int address;
}metrixLine;

int lineCounter(FILE *file);

metrixLine *mat;

void metrixParam (FILE *file)
{

    char s;
    int state = LABEL;
    int line;
    int addresCounter = 100;
    int i = 0;
    int j=0;
    line = lineCounter(file);
    mat = malloc(sizeof(metrixLine) * line);
    if (!mat)
    {
        printf("memory allocation failed");
        exit(0);
    }
    while (i<=line)
    {
        state = LABEL;
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
                        printf("First character on label in line %i is wrong\n", i);
                        exit(0);
                    }
                    else if (isalpha(s)== 0 && isdigit(s)==0 && j !=0 )
                        printf("Wrong character on label in line %i", i);
                    else
                    mat[i].label[j] = s;
                    j++;

                 }
                 else
                    state = COMMAND;
                    j = 0;
                }
                else if (state = COMMAND)
                {
                    if ((j==31 && s != ' ')|| (j==31 && s != '\t'))
                    {
                        printf("Memory crashed - the Command on line %i is too long");
                        exit(0);
                    }
                    else if ((j==0 && s != ' ')||(j==0 && s != '\t'))
                    {
                        mat[i].command[j] = s;
                        j++;
                    }
                    else if ((j>0 && s!=' ') || (j>0 && s!='\t'))
                    {
                        mat[i].command[j] = s;
                        j++;
                    }
                    else if ((j>0 && s==' ') || (j>0 && s=='\t'))
                    {
                        state = OPERAND1;
                        j==0;
                    }

                }
                else if (state = OPERAND1)
                {
                     if ((j==31 && s != ' ')|| (j==31 && s != '\t')||(j==31 && s != ','))
                    {
                        printf("Memory crashed - the Command on line %i is too long");
                        exit(0);
                    }
                      else if ((j==0 && s != ' ')||(j==0 && s != '\t')||(j==0 && s != ','))
                    {
                        mat[i].operand1[j] = s;
                        j++;
                    }
                    else if ((j>0 && s!=' ') || (j>0 && s!='\t')||(j==0 && s != ','))
                    {
                        mat[i].operand1[j] = s;
                        j++;
                    }
                    else if ((j>0 && s==' ') || (j>0 && s=='\t')||(j==0 && s != ','))
                    {
                        state = OPERAND2;
                        j==0;
                    }

                }
                else if (state = OPERAND2)
                {
                    {
                     if ((j==31 && s != ' ')|| (j==31 && s != '\t'))
                    {
                        printf("Memory crashed - the Command on line %i is too long");
                        exit(0);
                    }
                      else if ((j==0 && s != ' ')||(j==0 && s != '\t'))
                    {
                        mat[i].operand1[j] = s;
                        j++;
                    }
                    else if ((j>0 && s!=' ') || (j>0 && s!='\t'))
                    {
                        mat[i].operand1[j] = s;
                        j++;
                    }
                    else if ((j>0 && s==' ') || (j>0 && s=='\t'))
                    {
                        state = LABEL;
                        j==0;
                    }
                }

            }
            s = fgetc(file);

        }
        }
        while (s != '\n'|| s!= EOF)
        {
            s = fgetc(file);
        }
        i++;



    }
    while (i<=line)
    {
     printf ("%s\t%s\t%s\t%s\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2);
     i++;
    }
}


