#include <stdio.h>
#include <stdlib.h>


/*prototype*/

int metrixParam(FILE *file);

int main()
{
    int c;

    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File isn't exist");
        return 0;
    }

    metrixParam(file);
    fclose(file);
    return 0;
}
