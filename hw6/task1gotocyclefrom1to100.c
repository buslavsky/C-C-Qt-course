#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int i = 0;
    label:

    if(i<=99)
    {
        ++i;
        printf("%d\n",i);
        goto label;
    }

  return 0;
}
