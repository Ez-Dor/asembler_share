#include <stdio.h>
#include <stdlib.h>


/*prototype*/

int metrixParam(FILE *file);

int main()
{
    char c [31];
    int i, j;
    FILE *file = fopen ("input.txt", "r");
      if (file == NULL)
    {
        printf("File isn't exist");
        return 0;
    }
    fscanf(file," %s %s %s %s", &c,&c,&c,&c);
    printf("%s",c);
    /*metrixParam(file);*/
    fclose(file);
    return 0;
}
