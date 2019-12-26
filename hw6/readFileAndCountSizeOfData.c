#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *currentFile;
    int index;

    unsigned long fsize(char* file)
    {
    FILE * f = fopen("text.txt", "r");//fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
    }

    int lengthOfFile = fsize(currentFile);
    //currentFile = fopen("text.txt", "r");
    if(lengthOfFile > 0)
    {
        printf("The length of our file is %d bytes.", lengthOfFile);
    }
    else
        printf("Error: you must have file text.txt in application directory!!!");
    return 0;
}
