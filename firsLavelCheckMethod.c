/*All the check that have to be done on the input to be sure they legal*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asembler.h"

/*Check command and its operands in line i*/
int checkCommand (char com[], int i)
{
    /*Two operand required for these commands*/
    if (    !strcmp("mov1", com) || !strcmp("mov2", com) ||
            !strcmp("cmp1", com) || !strcmp("cmp2", com) ||
            !strcmp("add1", com) || !strcmp("add2", com) ||
            !strcmp("sub1", com) || !strcmp("sub2", com) ||
            !strcmp("lea1", com) || !strcmp("lea2", com))
    {
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) != 0)
            return TRUE;
        else
        {
            printf("Did not find two operands for command %s in line %i\n", com, getInputLine(i));
            return FALSE;
        }
    }

    /*One operand required for these commands*/
    if(     !strcmp("clr1", com) || !strcmp("clr2", com) ||
            !strcmp("inc1", com) || !strcmp("inc2", com) ||
            !strcmp("dec1", com) || !strcmp("dec2", com) ||
            !strcmp("jmp1", com) || !strcmp("jmp2", com) ||
            !strcmp("bne1", com) || !strcmp("bne2", com) ||
            !strcmp("red1", com) || !strcmp("red2", com) ||
            !strcmp("prn1", com) || !strcmp("prn2", com) ||
            !strcmp("jsr1", com) || !strcmp("jsr2", com) )
    {
        if (strlen(getData(i, OPERAND1)) == 0 && strlen(getData(i, OPERAND2)) != 0)
            return TRUE;

        else
        {
            printf("Found none or more than one operand in command %s in line %i\n", com, getInputLine(i));
            return FALSE;
        }
    }

    /*Special case not*/
    if (!strcmp("not1", com) || !strcmp("not2", com))
    {
        if (strlen(getData(i, OPERAND1)) == 0 && strlen(getData(i, OPERAND2)) != 0)
            if (isRegister(getData(i, OPERAND1)))
                return TRUE;
            else
            {
                printf("Command %s in line %i must get a register as an operand\n", com, getInputLine(i));
                return FALSE;
            }
        else
        {
            printf("Found none or more than one operand in command %s in line %i\n", com, getInputLine(i));
            return FALSE;
        }

    }

    /*No Operator required for these commands*/
    if (    !strcmp("rts1", com) || !strcmp("rts2", com) ||
            !strcmp("stop1", com) || !strcmp("stop2", com))
    {
        if (strlen(getData(i, OPERAND1)) == 0 && strlen(getData(i, OPERAND2)) == 0)
            return TRUE;
        else
        {
            printf("Found an operand for command %s in line %i\n", com, getInputLine(i));
            return FALSE;
        }
    }

    /*string or data?*/
    if (!strcmp(".string", com) || !strcmp(".data", com))
    {
        return TRUE;
    }

    printf("Found wrong command %s in line %i\n",com, getInputLine(i));

    return FALSE;
}

/*Run all over the the matrix with the input and use checkCommands to get validation */
int checkAllCommands ()
{
    extern int line;
    int i=1;
    int flag = TRUE;
    while (i<=line)
    {
        if(!checkCommand(getData(i, COMMAND), i))
            flag=FALSE;
        i++;
    }

    return flag;
}

/*Run all over the input and check for one label*/
int checkLabels ()
{
    char temp1 [31];
    char temp2 [31];
    extern int line;
    int i=1;
    int j=1;
    int flag = TRUE;
    while (i<=line)
    {
        strcpy(temp1,getData(i,LABEL));
        while (j<=line)
        {
            strcpy(temp2,getData(j,LABEL));
            if (j!=i && strlen(temp1) != 0 && strlen(temp2) != 0)
            {
                if(strcmp(temp1,temp2)==0)
                    return flag = FALSE;

            }

            j++;
        }
        i++;
    }
    return flag;
}

/*
int checkOperands ()
{
    if (two operands)
        checkOperand1
        checkOperand2

    if (one operand)
        if not, must be register
        else if is label/register
        else error
    return
}*/

/*Draft delete on Saturday*/
int checkOperand1 (char oper[], int i)
{
    extern int line;
    int temp[31];
    int x=1;
    int flag = FALSE;
    int j;
    int length = strlen(oper);
    int counter =0;
    char* s = " ";
    if(!changeDollars())
        return FALSE;
    /*NUMBER*/
    if (oper[0] == '#')
    {
        if (length<2)
        {
            printf("Wrong operand %s in line %i\n", oper, getInputLine(i));
        }
        else if (length==2)
        {
            if (isdigit(oper[1]))
                flag = TRUE;
            else if ((oper[1]=='-'||oper[1]=='+') && isdigit(oper[1])!=0)
                flag = TRUE;
            else
                printf("Wrong operand %s in line %i, # must be followed by a number \n", oper, getInputLine(i));
        }
        if (length>2)
        {
            flag = TRUE;
            for(j=2; j==length-1; i++)
            {
                if (!isdigit(oper[i]))
                    flag = FALSE;
            }
        }
    }/*end number*/
    else if (isRegister(oper))
        flag = TRUE;
    else
    {
        FILE *fp = fopen("input.ext","r");
        while (s)
        {
            fscanf(fp, s);
            if (strcmp(s,oper))
            {
                flag =TRUE;
                s = NULL;
            }
        }
        fclose(fp);
        if(isLabel(oper,OPERAND1)==2)
            flag = TRUE;
        else
            printf("Operand %s in line %i is not declared",oper,getInputLine(i));
    }
    return flag;
}

int checkOperand2 (char oper[], int i)
{
    int flag = FALSE;
    if (isLabel(oper, OPERAND2))
        flag = TRUE;
    else if (isRegister(oper))
        flag = TRUE;

    else
        printf("Illegal operand %s in line %i", oper, getInputLine(i));

    return flag;
}

int isLabel(char operand[], int param)
{
    extern int line;
    char c [MAX_INPUT];
    int i = 1;
    int flag = FALSE;
    while (i<line)
    {
        /*Check in the label column*/
        if (strcmp(getData(i, param), operand) == 0)
        {
            i=line;
            flag = TRUE;
            if (strcmp(getData(i,COMMAND),".string")==0)
                return 2;
            else if(strcmp(getData(i,COMMAND),".data")==0)
                return 2;
        }
        i++;
    }
    FILE *fp = fopen("output.ext","r");
    for((fscanf(fp,c));c!=EOF;(fscanf(fp,c)))
    {
        if(!strcmp(operand,c))
        {
            fclose(fp);
            return 2;
        }

    }
    fclose(fp);
    return flag;
}

/*check if is a register*/
int isRegister(char oper[])
{
    if (!strcmp(oper, "r0") || !strcmp(oper, "r1") ||
            !strcmp(oper, "r2") || !strcmp(oper, "r3") ||
            !strcmp(oper, "r4") || !strcmp(oper, "r5") ||
            !strcmp(oper, "r6") || !strcmp(oper, "r7") )
        return TRUE;
    return FALSE;
}

/*To finish the table we have to change the double dollar operator to the prev operand and check for valid*/
int changeDollars()
{
    extern int line;
    char temp [MAX_INPUT];
    int i=1;
    strcpy(temp,getData(i,OPERAND1));
    if (!strcmp(temp,"$$"))
    {
        printf("Illegal operand %s in line %i, cannot be used in the first line of the program\n", temp, getInputLine(i));
        return FALSE;
    }
    for (i=2; i<=line; i++)
    {
        strcpy(temp,getData(i,OPERAND1));
        if (!strcmp(temp,"$$"))
        {
            if(strlen(getData(i-1,OPERAND1))<=1)
            {
                printf("Illegal operand %s in line %i, previous operand missing\n", temp, getInputLine(i));
                return FALSE;
            }
            strcpy(temp,getData(i-1,OPERAND1));
            setData(i,OPERAND1,temp);
        }
    }
    return TRUE;
}


int strlenWithoutSpace(char c[])
{
    int i,count;
    int len=strlen(c);
    for (count=0,i=0;i<len;i++)
        if(!isspace(c[i]))
            count++;
    return count;

}
