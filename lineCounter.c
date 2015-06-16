#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int lines;

int lineCounter (FILE *file)
{

    char s;
    if (fgetc(file)!= EOF)
        lines++;

    while ((s = fgetc(file))!= EOF)
    {
        if (s == '\n')
            lines++;
    }
    return lines;
}
