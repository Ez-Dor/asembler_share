#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "asembler.h"

typedef struct
{
    char label [31];
    char command [31];
    char operand1 [31];
    char operand2 [31];
     int address;
}metrixLine;

metrixLine *m;

void metrix (FILE *file)
{
    int line;
    int i = 0;
    int j=0;
    line = lineCounter(file);
    mat = malloc(sizeof(metrixLine) * line);
    if (!mat)
    {
        printf("memory allocation failed");
        exit(0);
    }
    while (i<line)
    {
        fscanf(file,"%s %s %")
    }
}
