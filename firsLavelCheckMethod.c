/*All the check that have to be done on the input to be sure they legal*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asembler.h"


/*Accepts a string value and checks if it's a legal command.*/
int checkCommand (char com[])
{


    if      (!strcmp("mov1", com) || !(strcmp("mov2", com)))
        return TRUE;

    else if (!strcmp("cmp1", com) || !(strcmp("cmp2", com)))
        return TRUE;

    else if (!strcmp("add1", com) || !(strcmp("add2", com)))
        return TRUE;

    else if (!strcmp("sub1", com) || !(strcmp("sub2", com)))
        return TRUE;

    else if (!strcmp("lea1", com) || !(strcmp("lea2", com)))
        return TRUE;

    else if (!strcmp("not1", com) || !(strcmp("not2", com)))
        return TRUE;

    else if (!strcmp("clr1", com) || !(strcmp("clr2", com)))
        return TRUE;

    else if (!strcmp("inc1", com) || !(strcmp("inc2", com)))
        return TRUE;

    else if (!strcmp("dec1", com) || !(strcmp("dec2", com)))
        return TRUE;

    else if (!strcmp("jmp1", com) || !(strcmp("jmp2", com)))
        return TRUE;

    else if (!strcmp("bne1", com) || !(strcmp("bne2", com)))
        return TRUE;

    else if (!strcmp("red1", com) || !(strcmp("red2", com)))
        return TRUE;

    else if (!strcmp("prn1", com) || !(strcmp("prn2", com)))
        return TRUE;

    else if (!strcmp("jsr1", com) || !(strcmp("jsr2", com)))
        return TRUE;

    else if (!strcmp("rts1", com) || !(strcmp("rts2", com)))
        return TRUE;

    else if (!strcmp("stop1", com) || !(strcmp("stop2", com)))
        return TRUE;

    else
        return FALSE;
}

/*Run all over the the matrix withe the input and use checkCommands to get validation */
int checkAllCommands ()
{
    extern int line;
    int i=1;
    int flag = TRUE;
    while (i<=line)
    {
        if(checkCommand(getData(i, COMMAND)))
        {
            printf("Found command: %s\n", getData(i, COMMAND));
        }
        else
        {
            printf("Found wrong command: %s\n", getData(i, COMMAND));
            flag=FALSE;
        }
        i++;
    }
    return flag;
}
