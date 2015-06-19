/*This function count the lines on file */
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>



int lineCounter (FILE *file)
{
    int counter = 0;
    char c;
    /*Going back to begining of the file*/
    fseek(file,SEEK_SET,0);
    /*Check if have 1 line at least */
    if (fgetc(file)!= EOF)
        counter++;

    while ((c = fgetc(file))!= EOF)
    {
        if (c == '\n')
            counter++;
    }
/*return number lines */
    return counter;
}
