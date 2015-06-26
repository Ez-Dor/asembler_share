/*The main use for tests until EOP (like EOF but for our project;)*/
#include <stdio.h>
#include <stdlib.h>
#include "asembler.h"

int main(){
    int flag;
    char* c;
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File does not exist");
        return 0;
    }
    flag = buildMatrix(file);
    printMatrix();

/*    printf("\n%i",checkLabels());
    c = getData(4,OPERAND2);
    setData(4,OPERAND2,getData(1,OPERAND2));
    setData(1,OPERAND2,c);
    printf("%s\n",c);
    printf("Result is: %i\n",checkAllCommands());
   printf("result for %s: %d\n", getData(1, OPERAND1), checkOperand1(getData(1, OPERAND1), 1));
   setData(1,LABEL,c);
   printf("\n%i",checkLabels());
   printMatrix();*/
  freeMatrixMem();
    fclose(file);
    return 0;
}
