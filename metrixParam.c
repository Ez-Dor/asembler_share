/*
Matrix Parameters by Dor A & Lior F
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
    int emptyLines=0;
    int i=1;
    int j=0;
    int x=0;
    int y=0;
    char temp [] = "abcdef";
    /*Overwrite old files*/
    FILE *ent = fopen("output.ent","w");
    FILE *ext = fopen("output.ext","w");
    fclose(ent);
    fclose(ext);
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

    while (i<=line)
    {
        state = LABEL;
        /*Checks if there is any data that needs to go to external files and outputs it*/
        if (s == '.')
        {   y++;
            line--;
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
            /*If neither, skip the row and print error*/
            else
            {
                printf("Error! Wrong input in line %i", i+y-1);
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
                while (s==' ' || s=='\t')
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
                        printf("Memory crashed - the label on line %i is more then 30 characters\n",i+y);
                        state = COMMAND;
                        j = 0;
                    }
                    else if(s != ':')
                    {
                        if (j==0 && isalpha(s) == 0)
                        {
                            printf("The first character on the label in line %i is wrong\n", i+y);
                            mat[i].label[j] = s;
                            j++;
                        }
                        else if (isalpha(s)== 0 && isdigit(s)==0 && j !=0 )
                        {
                            printf("Wrong character found on label in line %i\n", i+y);
                            mat[i].label[j] = s;
                            j++;
                        }
                       /* printf("%i %i\t",i,j);*/
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
                        printf("Memory crashed - the Command on line %i is too long\n",i+y);
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
                        printf("Memory crashed - the operand1 on line %i is too long\n",i+y);
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
                        printf("Memory crashed - the operand2 on line %i is too long\n",i+y);
                        exit(0);
                    }
                    else if (j<MAX_INPUT)
                    {
                        mat[i].operand2[j] = s;
                        j++;
                    }
                }

                s = fgetc(file);
            }
            mat[i].address = addressCounter;
            addressCounter++;
            i++;
        }
        j=0;
        s = fgetc(file);
    }
    /*Free all the empty lines on our matrix*/
    emptyLines = line+y;
    while (line<emptyLines)
    {
        free(mat[emptyLines].label);
        free(mat[emptyLines].command);
        free(mat[emptyLines].operand1);
        free(mat[emptyLines].operand2);
        emptyLines--;
    }
}
/*Prints a line of the matrix*/
void printLine(int i)
{
    /*Print line I*/
    if(i<=line)
        printf("%s\t%s\t%s\t%s\t%i\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2,mat[i].address);
    else
        printf("error line %i does not exist",i);
}

/*Prints the whole matrix with a loop*/
void printMatrix()
{
    int i=1;
    while(i<=line)
    {
        printf("%s\t%s\t%s\t%s\t%i\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2,mat[i].address);
        i++;
    }
}

char* getParam(int index, int param)
{
    if(index>line)
     return "Index out of bounds";
    if (param == LABEL)
        return mat[index].label;

    else if (param == COMMAND)
        return mat[index].command;

    else if (param == OPERAND1)
        return mat[index].operand1;

    else if (param == OPERAND2)
        return mat[index].operand2;

    else
        return "Error parameter was not found";
}

int checkAllCommands ()
{
    int i=1;
    int flag = TRUE;
    while (i<=line)
    {
        if(checkCommand(getParam(i, COMMAND)))
        {
            printf("Found command: %s\n", mat[i].command);
        }
        else
        {
            printf("Found wrong command: %s\n", mat[i].command);
            flag=FALSE;
        }
        i++;
    }
    return flag;
}

/*Set ant parameter on our matrix - *does not work yet Dor fix* */
void setParam (int index, int param,char newParam [])
{
    if(index<=line)
    {
      if (param == LABEL)
        *mat[index].label = newParam;

    else if (param == COMMAND)
        *mat[index].command = newParam;

    else if (param == OPERAND1)
        *mat[index].operand1 = newParam;

    else if (param == OPERAND2)
        *mat[index].operand2 = newParam;
    }

    else
        printf ("Error, parameter or index out of bounds");
}

/*Free all memory of mat*/
void freeMatrixParam ()
{
    int i=0;
        while (i<line)
    {
        free(mat[i].label);
        free(mat[i].command);
        free(mat[i].operand1);
        free(mat[i].operand2);
        i++;
    }
}
