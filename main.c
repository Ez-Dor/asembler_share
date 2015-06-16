#include <stdio.h>
#include <stdlib.h>
#include "asembler.h"

/*prototype*/
int lineCounter(FILE *file);

int main()
{
    char d;
    int c;
    if (d == NULL)
        return printf("yep");
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File isn't exist");
        return 0;
    }
    c = lineCounter(file);
    printf("%i", c);
    fclose(file);
    return 0;
}
