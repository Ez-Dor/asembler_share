/*The main use for tests until EOP (like EOF but for our project;)*/
#include <stdio.h>
#include <stdlib.h>
#include "asembler.h"

int main(){
    int flag;
    char* c = "           ";
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File does not exist");
        return 0;
    }
    flag = buildMatrix(file);
    if(!flag)
    {
        printf("error!!!!!");
        exit(0);
    }
    changeDollars();
    printMatrix();

  printf("\n%i",checkLabels());
  printf("\n%i",flag);
  printf("\n%i", checkAllCommands());


  freeMatrixMem();
    fclose(file);
    return 0;
}
