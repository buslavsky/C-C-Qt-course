#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(){

    double x = DBL_MAX;

    printf("x initially was: %f \n", x);

    x = x*2;

    printf(" x now is: %f \n", x);

  return 0;

}