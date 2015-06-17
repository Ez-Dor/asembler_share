#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "asembler.h"



int lineCounter(FILE *file);
char otherFile (char k, FILE *file2);
char closeSpaces (char space, FILE *file1);

metrixLine *mat;

void metrixParam (FILE *file)
{

    char s = fgetc(file);
    int state = LABEL;
    int line;
    /*int addressCounter = 100;*/
    int i = 0;
    int j=0;
    line = lineCounter(file);
    mat = malloc(sizeof(metrixLine) * line);
    if (!mat)
    {
        printf("memory allocation failed");
        exit(0);
    }
    while (i<line)
    {
         printf("1\n");
        if (s == '.')
        {
            printf("2\n");
            s = otherFile (s,file);
            printf("4\n");
        }
        if (s==' ')
        {
         s=closeSpaces(s,file);
        }
        state = LABEL;
            while (s!= '\n' || s != EOF)
            {
                 printf("%c\n",s);

                if(state == LABEL)
                {
                 if(j == 31 && s != ':')
                 {
                    printf("Memory crashed - the Label on line %i is more then 30 characters\n",i);
                     state = COMMAND;
                    j = 0;
                 }
                 else if(s != ':')
                 {
                    if (j==0 && isalpha(s) == 0)
                    {
                        printf("First character on label in line %i is wrong\n", i);
                    }
                    else if (isalpha(s)== 0 && isdigit(s)==0 && j !=0 )
                    {
                        printf("Wrong character on label in line %i\n", i);
                    }


                    mat[i].label[j] = s;
                    j++;

                 }
                 else
                 {
                    state = COMMAND;
                    j = 0;
                 }

                }
                else if (state == COMMAND)
                {
                    if ((j==31 && s != ' ')|| (j==31 && s != '\t'))
                    {
                        printf("Memory crashed - the Command on line %i is too long\n",i);
                        state = OPERAND1;
                    j = 0;
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
                        j=0;
                    }

                }
                else if (state == OPERAND1)
                {
                     if ((j==31 && s != ' ')|| (j==31 && s != '\t')||(j==31 && s != ','))
                    {
                        printf("Memory crashed - the Command on line %i is too long\n");
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
                        j=0;
                    }

                }
                else if (state == OPERAND2)
                {
                    {
                     if ((j==31 && s != ' ')|| (j==31 && s != '\t'))
                    {
                        printf("Memory crashed - the Command on line %i is too long\n");
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
                        j=0;
                    }
                }

            }
             printf("%c\n",s);
            s = fgetc(file);

        }
        i++;
        s = fgetc(file);
    }
}

char closeSpaces (char space, FILE *file1)
{

    while (space == ' ')
    {

        space=fgetc(file1);
    }
    return space;
}

char otherFile (char k, FILE *file2)
{
    int i =4;
     printf("3\n");
    while (k!='\n')
    {
         printf("%i\n",i);
        k=fgetc(file2);
        i++;
    }
    return k;
}

