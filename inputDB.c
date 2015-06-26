/*
Build Matrix by Dor A & Lior F
Gets input from file, allocates memory and sorts them in a structure.
Include methods to get set and print the data on the memory
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
    int inputLine;
} matrixLine;


/*Global variable*/
matrixLine *mat;
int line;
int buildMatrix (FILE *file)
{

    /*Variables*/
    char s;
    int counter=1;
    int state = LABEL;
    int allLines=0;
    int i=1;
    int j=0;
    int x=0;
    int y=0;
    int flag = TRUE;
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
    mat = calloc(line, sizeof(matrixLine));
    if (!mat)
    {
        printf("Memory allocation failed");
        exit(0);
    }

    while (i<=line)
    {
        mat[i].inputLine = counter;
        counter++;
        state = LABEL;
        /*If have a comment skip line*/
        if (s==';')
            {
                while (s!='\n')
                {

                    s=fgetc(file);
                }
                y++;
            }
        /*Checks if there is any data that needs to go to external files and outputs it*/
        else if (s == '.')
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
                flag = FALSE;
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
                while ((s==' ' && s!='\n' && s != EOF) || (s=='\t'&& s!='\n' && s != EOF))
                {

                    s=fgetc(file);
                }
                if (s=='\n' || s == EOF)
                {
                    line--;
                    y++;
                }

                else
                    state = COMMAND;
            }
            /*Insert elements into the structure by states*/
            while (s!= '\n' && s != EOF)
            {
                if(state == LABEL)
                {
                    if(j == MAX_INPUT && s != ':')
                    {
                        flag = FALSE;
                        printf("Memory crashed - the label on line %i is more then 30 characters\n",i+y);
                        state = COMMAND;
                        j = 0;
                    }
                    else if(s != ':')
                    {
                        if (j==0 && isalpha(s) == 0)
                        {
                            flag = FALSE;
                            printf("The first character on the label in line %i is wrong\n", i+y);
                            mat[i].label[j] = s;
                            j++;
                        }
                        else if (isalpha(s)== 0 && isdigit(s)==0 && j !=0 )
                        {
                            flag = FALSE;
                            printf("Wrong character found on label in line %i\n", i+y);
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
                        flag = FALSE;
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
                        flag = FALSE;
                        printf("Memory crashed - the operand1 on line %i is too long\n",i+y);
                        state = OPERAND2;
                        j=0;
                    }
                    else if (j>=0 && s != ' ' && s != '\t' && s != ',')
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
                        flag = FALSE;
                        printf("Memory crashed - the operand2 on line %i is too long\n",i+y);
                        exit(0);
                    }
                    else if (j<MAX_INPUT && s!=' ' && s!='\t')
                    {
                        mat[i].operand2[j] = s;
                        j++;
                    }
                }

                s = fgetc(file);
            }
            i++;
        }
        j=0;
        s = fgetc(file);
    }
/*Now check if have ant ext or ent that insrt to command cuz the line doesn't start wit dot - and fix it*/
    i=0;
    while (i<=line)
    {
        x=0;
        strcpy(temp,mat[i].command);
        if (strcmp(".entry", temp)==0)
            {
                FILE *ent = fopen("output.ent","a");
                fputs(mat[i].operand1,ent);
                fclose(ent);
                x=1;
            }
        else if (strcmp(".extern", temp)==0)
            {
                FILE *ext = fopen("output.ext","a");
                fputs(mat[i].operand1,ext);
                fclose(ext);
                x=1;
            }
        if(x!=0)
       {
           j=i;
           while (j<line)
           {
               strcpy(mat[j].label,mat[j+1].label);
               strcpy(mat[j].command,mat[j+1].command);
               strcpy(mat[j].operand1,mat[j+1].operand1);
               strcpy(mat[j].operand2,mat[j+1].operand2);
               mat[j].inputLine = mat[j+1].inputLine;
               j++;
           }
           line--;
           y++;
       }
       i++;
    }
    /*Free all the empty lines on our matrix*/
    allLines = line+y;
    while (line<allLines)
    {
        free(mat[allLines].label);
        free(mat[allLines].command);
        free(mat[allLines].operand1);
        free(mat[allLines].operand2);
        free(&mat[allLines].inputLine);
        allLines--;
    }
    return flag;
}
/*Prints a line of the matrix*/
void printLine(int i)
{
    /*Print line I*/
    if(i<=line)
        printf("%s\t%s\t%s\t%s\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2);
    else
        printf("error line %i does not exist",i);
}

/*Prints the whole matrix with a loop*/
void printMatrix()
{
    int i=1;
    while(i<=line)
    {
        printf("%i  ",mat[i].inputLine);
        printf("%s\t%s\t%s\t%s\n",mat[i].label,mat[i].command,mat[i].operand1,mat[i].operand2);
        i++;
    }
}

char* getData(int index, int param)
{
    if(index>line || index<1)
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

int getInputLine (int i)
{
    if(i>line || i<0)
        return 0;
    else
        return mat[i].inputLine;
}


/*Set a parameter on our matrix */
void setData (int index, int param,char data [])
{
    if(index<=line || index>=1)
    {
      if (param == LABEL)
        strcpy(mat[index].label,data);

    else if (param == COMMAND)
        strcpy(mat[index].command,data);

    else if (param == OPERAND1)
        strcpy (mat[index].operand1,data);

    else if (param == OPERAND2)
        strcpy(mat[index].operand2,data);
    }

    else
        printf ("Error, parameter or index out of bound\n");
}

/*Free all memory of mat*/
void freeMatrixMem ()
{
    free(mat);
    /*int i=0;
    while(i<=line)
    {
        free(mat[i].label);
        free(mat[i].command);
        free(mat[i].operand1);
        free(mat[i].operand2);
        free(mat[i].inputLine);
        i++;
    }*/

}
