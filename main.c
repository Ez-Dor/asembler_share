/*The main use for tests until EOP (like EOF but for our project;)*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asembler.h"

char* fileName;
int main(int argc, char* argv[])
{
    char inputFile[FILENAME_MAX];
    int flag = TRUE;
    int i;
    FILE *file;
    if(argc==1)
    {
        printf("No files to compile");
        return 0;
    }
    for(i=1; i<argc; i++)
    {
        fileName = argv[i];
        strcpy(inputFile,argv[i]);
        strcat(inputFile,".as");
        file = fopen (inputFile, "r");
        if (file == NULL)
        {
            printf("File %s does not exist",fileName);
            return 0;
        }

        if(!buildMatrix(file)||!changeDollars()||!checkLabels()||!checkAllCommands())
            flag = FALSE;
        printMatrix();
        printf("%i\n",flag);
        buildSymbolTable();
        printf("%i",lineIC(1));
        freeSTable();
        freeMatrixMem();
        fclose(file);

    }
    return 0;
}
