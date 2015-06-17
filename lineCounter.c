#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int lines = 0;

int lineCounter (FILE *file)
{

    char c;
    if (fgetc(file)!= EOF)
        lines++;

    while ((c = fgetc(file))!= EOF)
    {
        if (c == '\n')
            lines++;
    }
    return lines;
}
