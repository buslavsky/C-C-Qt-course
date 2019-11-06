#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
  char arr[1000];
  //If uncomment the two following rows, you'll get an explanation and help text ))
  //printf("As a comment, here we have rand max, for example: %d\n", RAND_MAX);
  //printf("And here we have a result of the task:\n");
  for(int i = 0; i <= 999;)
    {   
        int randCh = rand() % 127;
        char ch = randCh; //rand() % 127;
        if (isalpha(ch) !=0)
        {
            arr[i] = ch;
            putchar(arr[i]);
            ++i;
        }
    }
  return 0;
}