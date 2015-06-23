/*The main use for tests until EOP (like EOF but for our project;)*/
#include <stdio.h>
#include <stdlib.h>
#include "asembler.h"

int main()
{ int flag;
    char* c;
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File does not exist");
        return 0;
    }
    flag = buildMetrix(file);
    printMatrix();

     c = getData(11,OPERAND1);
    printf("%s\n",c);
    printf("%i",checkAllCommands());
    freeMatrixParam();
    fclose(file);
    return 0;
}
