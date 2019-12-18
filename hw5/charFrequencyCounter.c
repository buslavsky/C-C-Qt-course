#include <stdio.h>
#include <string.h>
#include <locale.h>


unsigned FrequencyArray[256];

int main( )
{
    setlocale(0, "");
    FILE *fileWithChars;

  	if ((fileWithChars = fopen("testFile.txt", "rt")) == NULL)
  	{
    		printf("File '%s' could not be read\n", "testFile.txt");
    		return 1;
  	}

   	memset(FrequencyArray, 0, 256 * sizeof(unsigned));

	while (!feof(fileWithChars))
    		FrequencyArray[fgetc(fileWithChars)] ++;

	printf("Chars and their appear frequencies:\n");

		for (int i = 0; i < 256; i ++)
    			if (FrequencyArray[i])
				{
					printf("Char %c appeared %5u times\n", i, FrequencyArray[i]);
				}
			return 0;
}
