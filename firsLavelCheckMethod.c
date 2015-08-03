/*All the check that have to be done on the input to be sure they legal*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "asembler.h"

/*Check command and its operands in line i*/
int checkCommand (char com[], int i)
{
    int flag = FALSE;

    /*Commands mov, add and sub
      Must have two operands
      Operand1 must be either Label, Register or legal numeric value
    */
    if (    !strcmp("mov1", com) || !strcmp("mov2", com) ||
            !strcmp("add1", com) || !strcmp("add2", com) ||
            !strcmp("sub1", com) || !strcmp("sub2", com) )
    {
        /*Do we have two operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) != 0)
        {
            /*Is Operand1 legal?*/
            if(isRegister(getData(i, OPERAND1)) || isLabel(getData(i, OPERAND1)) || isNumeric(getData(i, OPERAND1), i))
            {
                /*Is Operand2 legal?*/
                if (isRegister(getData(i, OPERAND2)) || isLabel(getData(i, OPERAND2)))
                {
                    flag = TRUE;
                }
                else
                {
                    printf("Ilegal operand %s in line %i\n", getData(i, OPERAND2), getInputLine(i));
                    flag = FALSE;
                }

            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("Did not find two operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }


    /*Command cmp
      Must have two operands
      Operands 1 and 2 must be either Label, Register or legal numeric value
    */
    if (  !strcmp("cmp1", com) || !strcmp("cmp2", com))
    {
        /*Do we have two operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) != 0)
        {
            /*Is Operand1 legal?*/
            if(isRegister(getData(i, OPERAND1)) || isLabel(getData(i, OPERAND1)) || isNumeric(getData(i, OPERAND1), i))
            {
                /*Is Operand2 legal?*/
                if (isRegister(getData(i, OPERAND1)) || isLabel(getData(i, OPERAND1)) || isNumeric(getData(i, OPERAND1), i))
                {
                    flag = TRUE;
                }
                else
                {
                    printf("Ilegal operand %s in line %i\n", getData(i, OPERAND2), getInputLine(i));
                    flag = FALSE;
                }

            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("Did not find two operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }

    /*Command lea
      Must have two operands
      Operand 1 must be a label
      Operand 2 must be either register or label
    */
    if (  !strcmp("lea1", com) || !strcmp("lea2", com))
    {
        /*Do we have two operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) != 0)
        {
            /*Is Operand1 legal?*/
            if(isLabel(getData(i, OPERAND1)))
            {
                /*Is Operand2 legal?*/
                if (isRegister(getData(i, OPERAND1)) || isLabel(getData(i, OPERAND1)))
                {
                    flag = TRUE;
                }
                else
                {
                    printf("Ilegal operand %s in line %i\n", getData(i, OPERAND2), getInputLine(i));
                    flag = FALSE;
                }

            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("Did not find two operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }
    /*Command not
      Must have one operand
      Operands 1 must be  register
    */
    if (  !strcmp("not1", com) || !strcmp("not2", com))
    {
        /*Do we have one operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) == 0)
        {
            /*Is Operand1 legal?*/
            if(isRegister(getData(i, OPERAND1)))
            {
                flag = TRUE;
            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("More than one or no operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }
    /*Commands clr, inc. dec, jmp, bne, red
      Must have one operands
      Operands 1 must be either Register or Label
    */
    if(     !strcmp("clr1", com) || !strcmp("clr2", com) ||
            !strcmp("inc1", com) || !strcmp("inc2", com) ||
            !strcmp("dec1", com) || !strcmp("dec2", com) ||
            !strcmp("jmp1", com) || !strcmp("jmp2", com) ||
            !strcmp("bne1", com) || !strcmp("bne2", com) ||
            !strcmp("red1", com) || !strcmp("red2", com) )
    {
        /*Do we have one operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) == 0)
        {
            /*Is Operand1 legal?*/
            if(isRegister(getData(i, OPERAND1)) || isLabel(getData(i, OPERAND1)))
            {
                flag = TRUE;
            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("More than one or no operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }

    /*Command prn
      Must have one operand
      Operands 1 must be either register, label or numeric
    */
    if (  !strcmp("prn1", com) || !strcmp("prn2", com))
    {
        /*Do we have one operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) == 0)
        {
            /*Is Operand1 legal?*/
            if(isRegister(getData(i, OPERAND1)) || isLabel(getData(i, OPERAND1)) || isNumeric(getData(i, OPERAND1), i))
            {
                flag = TRUE;
            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("More than one or no operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }

    /*Command jsr
      Must have one operand
      Operands 1 must be label
    */
    if (  !strcmp("jsr1", com) || !strcmp("jsr2", com))
    {
        /*Do we have one operands?*/
        if (strlen(getData(i, OPERAND1)) != 0 && strlen(getData(i, OPERAND2)) == 0)
        {
            /*Is Operand1 legal?*/
            if(isLabel(getData(i, OPERAND1)))
            {
                flag = TRUE;
            }
            else
            {
                printf("Ilegal operand %s in line %i\n", getData(i, OPERAND1), getInputLine(i));
                flag = FALSE;
            }
        }

        else
        {
            printf("More than one or no operands for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }
    /*
      Commands rts and stop
      Must have no operands
    */
    if (    !strcmp("rts1", com) || !strcmp("rts2", com) ||
            !strcmp("stop1", com) || !strcmp("stop2", com))
    {
        if (strlen(getData(i, OPERAND1)) == 0 && strlen(getData(i, OPERAND2)) == 0)
            flag = TRUE;
        else
        {
            printf("Found an operand for command %s in line %i\n", com, getInputLine(i));
            flag = FALSE;
        }
    }

    /*.data tests*/
    if (!strcmp(".data", com))
    {
        if(isData(i))
            flag = TRUE;
        else
        {
            printf("Ilegal values for .data command in line %i\n", getInputLine(i));
            flag = FALSE;
        }
    }

    /*.string tests*/
    if (!strcmp(".string", com))
    {
        if(isString(i))
            flag = TRUE;
        else
        {
            printf("Ilegal values for .string command in line %i\n", getInputLine(i));
            flag = FALSE;
        }
    }

    if (flag==FALSE)
        printf("Found wrong command or ilegal operands in line %i\n", getInputLine(i));

    return flag;
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
                {
                  flag = FALSE;
                  printf("Found duplicate label in line %i and line %i\n",getInputLine(i), getInputLine(j));
                }


            }

            j++;
        }
        i++;
    }
    return flag;
}

/*Test for existing and legal label*/
int isLabel(char operand[])
{
    extern int line;
    int i = 1;
    while (i<=line)
    {

        /*Check in the label column*/
        if (strcmp(getData(i, LABEL),operand) == 0)
        {

            if (strcmp(getData(i,COMMAND),".string")==0)
                return TRUE;
            else if(strcmp(getData(i,COMMAND),".data")==0)
                return TRUE;


        }

        i++;
    }
    return isExtern(operand);
}

int isExtern(char param[])
{
    FILE *fp;
    char c [MAX_INPUT];
    char fileExt[FILENAME_MAX];
    extern char* fileName;
    strcpy(fileExt,fileName);
    strcat(fileExt,".ext");
    fp = fopen(fileExt,"r");
    if(!fp)
        return FALSE;
    while((fscanf(fp,"%s",c))==1)
    {
        if(!strcmp(param,c))
        {
            fclose(fp);
            return TRUE;
        }

    }
    fclose(fp);
    return FALSE;
}
int isEntry(char param[])
{
    FILE *fp;
    char c [MAX_INPUT];
    char fileEnt[FILENAME_MAX];
    extern char* fileName;
    strcpy(fileEnt,fileName);
    strcat(fileEnt,".ent");
    fp = fopen(fileEnt,"r");
    if(!fp)
        return FALSE;
    while((fscanf(fp,"%s",c))==1)
    {
        if(!strcmp(param,c))
        {
            fclose(fp);
            return TRUE;
        }

    }
    fclose(fp);
    return FALSE;
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

/*check if Operand is a numeric value*/
int isNumeric(char oper[], int i)
{
    int flag = FALSE;
    int length = strlen(oper);
    int value;
    int j;
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
            else
                printf("Wrong operand %s in line %i, # must be followed by a number \n", oper, getInputLine(i));
        }

        else if (length>2)
        {
           if (oper[1]=='-'|| oper[1]=='+' || isdigit(oper[1]))
           {
                flag=TRUE;
                for(j=2; j<length; j++)
                {
                    if (!(isdigit(oper[j])))
                    {
                        flag = FALSE;
                        printf("Wrong value \"%c\" in line %i", oper[j], getInputLine(i));
                    }

                }
           }
           else
           {
                printf("Wrong operand %s in line %i, # must be followed by a number \n", oper, getInputLine(i));
           }

            /*Check that the numeric value is in range*/
            value = strtol(oper+1, NULL, 10);

            if (value > DIRECTMAX || value < DIRECTMIN)
            {
                printf("Numeric value of operand %s in line %i is out of bounds", oper, getInputLine(i));
                flag = FALSE;
            }
        }
    }/*end number*/
    return flag;
}

/*Check if .Data has legal values*/
int isData(int i)
{
    char str [31];
    int state = COMMA;
    int len;
    int bigflag =TRUE;
    int flag;
    int j = 0;
    int num;

    strcpy(str, getData(i, OPERAND1));
    len = strlen(str);
    if(len>0)
    {
        while(j<len)
        {
            if(isdigit(str[j]) || str[j]=='+' || str[j] == '-')
            {
                num = strtol(str+j, NULL, 10);
                if (num<MINDATANUM || num>MAXDATANUM)
                {
                    printf("Number %d out of bound in line %i\n", num, getInputLine(i));
                    bigflag = FALSE;
                }

            }
            else
            {
                bigflag = FALSE;
                printf("ilegal value %c in line %i col %i\n", str[j], getInputLine(i), j);
            }
            j++;
        }
    }

    j=0;
    state=COMMA;
    strcpy(str, getData(i, OPERAND2));
    len = strlen(str);
    if(len>0)
    {
        while(j<len)
        {
            flag = FALSE;
            if(state==COMMA && flag==FALSE)
            {
                if(isdigit(str[j]) || str[j]=='+' || str[j] == '-')
                {
                    state=NUMBER;
                    flag = TRUE;
                    num = strtol(str+j, NULL, 10);
                    if (num<MINDATANUM || num>MAXDATANUM)
                    {
                        printf("Number %d out of bound in line %i\n", num, getInputLine(i));
                        bigflag = FALSE;
                    }

                }

                if(str[j]!=' ' && state==COMMA && flag==FALSE)
                {
                    printf("ilegal value %c in line %i\n", str[j], getInputLine(i));
                    bigflag = FALSE;
                }
            }

            if(state==NUMBER && flag==FALSE)
            {
                if(!isdigit(str[j]))
                {
                    if(str[j]==',')
                    {
                        state=COMMA;
                        flag =TRUE;
                    }

                    if(str[j]!=' ' &&state==NUMBER && flag==FALSE)
                    {
                        printf("ilegal character \"%c\" in line %i\n", str[j], getInputLine(i));
                        bigflag = FALSE;
                    }

                }
            }
            j++;
        }
    }
    return bigflag;
}

/*Check if .String has legal values*/
int isString(int i)
{
    char str [64];
    int flag=FALSE;
    int len;

    strcpy(str, getData(i, OPERAND1));
    strcat(str, getData(i, OPERAND2));
    len = strlen(str);

    if(str[0]=='"' && str[len-1]=='"')
        flag = TRUE;

    return flag;
}

/*To finish the table we have to change the double dollar operator to the prev operand and check for valid*/
int changeDollars()
{
    extern int line;
    char temp [MAX_INPUT];
    int i=1;
    int flag = TRUE;
    /*Operand one checks*/
    strcpy(temp,getData(i,OPERAND1));
    if (!strcmp(temp,"$$"))
    {
        printf("Illegal operand %s in line %i, cannot be used in the first line of the program\n", temp, getInputLine(i));
        flag = FALSE;
    }
    for (i=2; i<=line; i++)
    {
        strcpy(temp,getData(i,OPERAND1));
        if (!strcmp(temp,"$$"))
        {
            if(!strlen(getData(i,OPERAND2)))
            {
                if( !strcmp(getData(i,COMMAND),"jmp1")||!strcmp(getData(i,COMMAND),"jmp2")||
                        !strcmp(getData(i,COMMAND),"bne1")||!strcmp(getData(i,COMMAND),"bne2")||
                        !strcmp(getData(i,COMMAND),"red1")||!strcmp(getData(i,COMMAND),"red2")||
                        !strcmp(getData(i,COMMAND),"prn1")||!strcmp(getData(i,COMMAND),"prn2"))
                {
                    if(strlen(getData(i-1,OPERAND2))<=1)
                    {
                        printf("Illegal operand %s in line %i, previous operand missing\n", temp, getInputLine(i));
                        flag = FALSE;
                    }
                    else
                    {
                        strcpy(temp,getData(i-1,OPERAND2));
                        setData(i,OPERAND2,temp);
                    }

                }
                else
                {
                    printf("Illegal operand %s in line %i, cannot be used in the %s command\n", temp, getInputLine(i),getData(i,COMMAND));
                    flag = FALSE;
                }
            }
            else
            {

                if(!strcmp(getData(i,COMMAND),"cmp1")||!strcmp(getData(i,COMMAND),"cmp2"))
                {
                    if(!strcmp(getData(i,OPERAND2),"$$"))
                    {
                        if(strlen(getData(i-1,OPERAND2))<=1)
                        {
                            printf("Illegal operand %s in line %i, previous operand missing\n", temp, getInputLine(i));
                            flag = FALSE;
                        }
                        strcpy(temp,getData(i-1,OPERAND2));
                        setData(i,OPERAND2,temp);
                    }
                }
                else if(!strcmp(getData(i,COMMAND),"lea1")||!strcmp(getData(i,COMMAND),"lea2"))
                {
                    printf("Illegal operand %s in line %i, cannot be used in the \"lea\" command\n", temp, getInputLine(i));
                    flag = FALSE;
                }
                if(strlen(getData(i-1,OPERAND1))<=1)
                {
                    printf("Illegal operand %s in line %i, previous operand missing\n", temp, getInputLine(i));
                    flag = FALSE;
                }
                strcpy(temp,getData(i-1,OPERAND1));
                setData(i,OPERAND1,temp);
            }
        }
    }

    return flag;
}


int strlenWithoutSpace(char c[])
{
    int i,count;
    int len=strlen(c);
    for (count=0,i=0; i<len; i++)
        if(!isspace(c[i]))
            count++;
    return count;

}
