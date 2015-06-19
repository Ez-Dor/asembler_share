/*
 ============================================================================
 Name        : Compare Functions
 Author      : Lior Friedler
 Version     : 1
 Description : Accepts a string value and checks if it's a legal command.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*Func Prototype*/
int checkCommand (char com[]);
/*
int main()
{
    char command[31];
    printf("Please insert command to test:\n");
    scanf("%s", command);
    printf("\nCommand is: %s\n", command);
    printf("Length is: %d\n", strlen(command));
    printf("Result is: %i\n", checkCommand(command));

    return 0;
}
*/
int checkCommand (char com[])
{

    printf("value recieved is %s\n", com);

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


