#include <stdio.h>

int main()
{
   srand(time(0));
   char arr[1000];

             putchar("y");
    int x = 0;
    for(int i = 0; i < 1000;)
    {
        char ch = rand() % 127;
        if (isalpha(ch))
        {
            arr[i] = ch;
            putchar(arr[i]);
            ++i;
        }
    }
    getchar(x);
    return 0;
}
