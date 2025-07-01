#include <stdio.h>
#include <math.h>

int main() {
     int l_new, l_old, C, N;
     float day;
     scanf("%d %d %d %d", &l_new,&l_old,  &C, &N);
     day = (float) C/ (((l_old - l_new)/1000.00)*N) ;
     day = ceil(day);
   printf("%d",(int)day);
   return 0;
  }

