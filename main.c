#include <stdio.h>
#include <stdlib.h>
#include "asembler.h"

/*prototype*/
int lineCounter(FILE *file);
int metrixParam(FILE *file);

int main()
{
    char d;
    int c;
    int i, j;
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File isn't exist");
        return 0;
    }
    c = lineCounter(file);
    printf("%i\n", c);
    metrixParam(file);
    fclose(file);
    return 0;
}
