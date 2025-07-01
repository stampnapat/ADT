#include <stdio.h>
#include <math.h>

int main() {
int x, y, z, sum;
char status1, status2;

scanf("%d %d %d", &x, &y, &z);
scanf(" %c %c", &status1, &status2);
 if (status1 == 'Y' || status1 == 'y') {
   if ( status2 == 'Y' || status2 == 'y'){
     sum = ceil((float)(x+y)/z);
 }else if ( status2 == 'N' || status2 == 'n' ){
     sum = x + y;
 }
}else {
 if (status2 == 'Y' || status2 == 'y'){
   sum = ceil((float)x/z);
 }else {
   sum = x;
 }
}

 printf("%d", sum);
