/*The main use for tests until EOP (like EOF but for our project;)*/
#include <stdio.h>
#include <stdlib.h>
#include "asembler.h"

/*prototype*/

int matrixParam(FILE *file);

int main()
{

    int i;
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File does not exist");
        return 0;
    }
    matrixParam(file);
    fclose(file);
    return 0;
}
