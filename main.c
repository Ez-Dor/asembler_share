#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asembler.h"

char* fileName;
int main(int argc, char* argv[])
{
    char inputFile[FILENAME_MAX];
    char temp[FILENAME_MAX];
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
        if (!file)
        {
            printf("File %s does not exist",fileName);
            return 0;
        }

        if(!buildMatrix(file)||!changeDollars()||!checkLabels()||!checkAllCommands())
            flag = FALSE;
        if(flag)
        {

            buildSymbolTable();
            buildOutputTable();
            freeTables();
            strcpy(temp,fileName);
            strcat(temp,".ex");
            remove(temp);
            strcpy(temp,fileName);
            strcat(temp,".en");
            remove(temp);
        }
        else
        {
            printf("Cannot compile %s.",fileName);
            strcpy(temp,fileName);
            strcat(temp,".ex");
            remove(temp);
            strcpy(temp,fileName);
            strcat(temp,".en");
            remove(temp);
        }

        freeMatrixMem();
        fclose(file);
    }
    return 0;
}
