/*
Matrix Parameters by Dor A
Gets input commands from file, allocates memory and sorts them in a structure.
*/

/*Include standard libraries and custom header*/
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "asembler.h"

/*This is the structure for a line of command*/


/*Function prototype*/
int lineCounter(FILE *file);
char otherFile (char k, FILE *file2);
char closeSpaces (char space, FILE *file1);

/*Global variable*/
matrixLine *mat;

void matrixParam (FILE *file)
{

    /*Variables*/
    char s;
    int state = LABEL;
    int line;
    int addressCounter = 100;
    int i = 0;
    int j=0;

    /*Use Line Counter to know how many lines are in the input file*/
    line = lineCounter(file);
    /*Set file pointer to start of file*/
    fseek(file,SEEK_SET,0);
    s = fgetc(file);

    /*Allocate memory for the matrix according to the lines.*/
    mat = malloc(sizeof(matrixLine) * line);

    if (!mat)
    {
        printf("Memory allocation failed");
        exit(0);
    }

    while (i<line)
    {
        state = LABEL;
        if (s == '.')
        {
/*DOR- Right now skips the line*/
            s = otherFile (s,file);
        }
        else
        {
            if (s==' '||s=='\t')
            {
                s=closeSpaces(s,file);
                state = COMMAND;
            }
            while (s!= '\n' && s != EOF)
            {
                if(state == LABEL)
                {
                    if(j == MAX_INPUT && s != ':')
                    {
                        printf("Memory crashed - the label on line %i is more then 30 characters\n",i);
                        state = COMMAND;
                        j = 0;
                    }
                    else if(s != ':')
                    {
                        if (j==0 && isalpha(s) == 0)
                        {
                            printf("The first character on the label in line %i is wrong\n", i);
                            mat[i].label[j] = s;
                            j++;
                        }
                        else if (isalpha(s)== 0 && isdigit(s)==0 && j !=0 )
                        {
                            printf("Wrong character found on label in line %i\n", i);
                            mat[i].label[j] = s;
                            j++;
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
                    if (j==MAX_INPUT && s != ' ' && s != '\t')
                    {
                        printf("Memory crashed - the Command on line %i is too long\n",i);
                        state = OPERAND1;
                        j = 0;
                    }
                    else if (j==0 && s != ' ' && s != '\t')
                    {
                        mat[i].command[j] = s;
                        j++;
                    }
                    else if (j>0 && s!=' ' && s!='\t')
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
                    if (j==MAX_INPUT && s != ' '&& s != '\t'&& s != ',')
                    {
                        printf("Memory crashed - the operand1 on line %i is too long\n");
                        state = OPERAND2;
                        j=0;
                    }
                    else if (j==0 && s != ' ' && s != '\t' && s != ',')
                    {
                        mat[i].operand1[j] = s;
                        j++;
                    }
                    else if (j>0 && s!=' '&& s!='\t' && s != ',')
                    {
                        mat[i].operand1[j] = s;
                        j++;
                    }
                    else if ((j>0 && s==' ') || (j>0 && s=='\t')||(j>0 && s == ','))
                    {
                        state = OPERAND2;
                        j=0;

                    }

                }
                else if (state == OPERAND2)
                {

                    if (j==MAX_INPUT && s != ' ' && s != '\t')
                    {
                        printf("Memory crashed - the operand2 on line %i is too long\n");
                        exit(0);
                    }
                    else
                    {
                        mat[i].operand2[j] = s;
                        j++;
                    }
                }

                s = fgetc(file);
            }
        mat[i].address = addressCounter;
        addressCounter++;
        }
        j=0;

        i++;
        s = fgetc(file);


    }
    i=0;

}

char closeSpaces (char space, FILE *file1)
{

    while (space != ' ' && space != '\t')
    {

        space=fgetc(file1);
    }
    return space;
}

char otherFile (char k, FILE *file2)
{
    while (k!='\n')
    {
        k=fgetc(file2);
    }
    return k;
}

