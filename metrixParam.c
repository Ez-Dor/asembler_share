/*
Matrix Parameters by Dor A
Gets input commands from file, allocates memory and sorts them in a structure.
*/

/*Include standard libraries and custom header*/
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "asembler.h"

/*This is the structure for a line of command*/
typedef struct
{
    char label [MAX_INPUT];
    char command [MAX_INPUT];
    char operand1 [MAX_INPUT];
    char operand2 [MAX_INPUT];
    int address;
} matrixLine;


/*Global variable*/
matrixLine *mat;
int line;
void matrixParam (FILE *file)
{

    /*Variables*/
    char s;
    int state = LABEL;
    int addressCounter = 100;
    int i = 0;
    int j=0;
    int x=0;
    char temp [] = "abcdef";
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
        /*Checks if there is any data that needs to go to external files and outputs it*/
        if (s == '.')
        {
            x=0;
            /*Run until the end of the word and check validality */
            while (x<6 && s!=' ' && s!='\t' && s!='\n' && s!=EOF)
            {
                s=fgetc(file);
                temp[x] = s;
                x++;
            }
            /*Checks if entry*/
            if (strcmp("entry ", temp)==0)
            {
                FILE *ent = fopen("output.ent","a");
                while (s!='\n' && s!=EOF)
                {
                    s=getc(file);
                    fputc(s,ent);
                }
                fputc(s,ent);
                fclose(ent);
            }
            /*Checks if external*/
            else if (strcmp("extern", temp)==0)
            {
                FILE *ext = fopen("output.ext","a");
                while (s!='\n' && s!=EOF)
                {
                    s=getc(file);
                    fputc(s,ext);
                }
                fputc(s,ext);
                fclose(ext);
            }
            /*if neither, skip the row and print error*/
            else
            {
                printf("Error! Wrong input in line %i", i);
                while (s!='\n' && s!=EOF)
                    s=getc(file);
            }
        }
        /*Done with entries and other things, run the rest of the input*/
        else
        {
            /*If the line is not a label, we skip spaces*/
            if (s==' '||s=='\t')
            {
                while (s!=' ' && s!='\t')
                {

                    s=fgetc(file);
                }
                state = COMMAND;
            }
            /*Insert elements into the structure by states*/
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
                    /*Done managing labels*/
                    /*Managing commands*/
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
                    /*managing Operands*/
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
}
/*Prints a line of the matrix*/
void printLine(int i)
{
    /*Print line I*/
    printf("%s\t%s\t%s\t%s\t%i\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2,mat[i].address);
}

/*Prints the whole matrix with a loop*/
void printMatrix()
{
    int i = 0;
    while(i<line)
    {
        printf("%s\t%s\t%s\t%s\t%i\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2,mat[i].address);
        i++;
    }
}

char* getParam(int index, int param)
{
    index--;
    if (param == LABEL)
        return mat[index].label;

    else if (param == COMMAND)
        return mat[index].command;

    else if (param == OPERAND1)
        return mat[index].operand1;

    else if (param == OPERAND2)
        return mat[index].operand2;

    else
        return "error";
}

