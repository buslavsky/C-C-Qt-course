#include <stdio.h>
#include <string.h>


unsigned FrequencyArray[256];

int main( )
{
  FILE *fileWithChars;
    	  
  	if ((fileWithChars = fopen("testFile.txt", "rt")) == NULL)
  	{
    		printf("Файл '%s' невозможно прочитать\n", "testFile.txt");
    		return 1;
  	}

   	memset(FrequencyArray, 0, 256 * sizeof(unsigned));
	
	while (!feof(fileWithChars))
    		FrequencyArray[fgetc(fileWithChars)] ++;
  	
	printf("Символы и частоты их появления:\n");
  		
		for (int i = 0; i < 256; i ++)
    			if (FrequencyArray[i])
				{
					printf("Символ %c появился %5u раз\n", i, FrequencyArray[i]);
				}
			return 0;
} 