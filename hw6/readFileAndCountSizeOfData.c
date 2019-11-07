#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   // setlocale(LC_ALL, "en_US.UTF-8");
    FILE *currentFile;

    unsigned long fsize(char* file)
    {
    FILE * f = fopen("text.txt", "r");//fopen(file, "r");
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fclose(f);
    return len;
    }

    int lengthOfFile = fsize(currentFile);
    printf("The length of our file is %d ", lengthOfFile);
    currentFile = fopen("text.txt", "r");
    if(lengthOfFile > 0)
    {
	    char charArray[1001] = {0};
	    fgets(charArray, 1001, currentFile);
        for(int i = 32; i<=256; i++)
        {
            int charNumber = 0;
            for(int j = 0; j < charArray; j++)
            {
                if(charArray[j]==i)
                    charNumber++;
            }
            printf("char \"%c\":%d\n", i, charNumber);
        }

    }
    else
        printf("Error: you must have file text.txt in application directory!!!");
    return 0;
}
