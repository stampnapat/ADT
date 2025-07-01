#include <stdio.h>
#include <math.h>

int main() {
int x, y, z, sum;
char status1, status2;

scanf("%d %d %d", &x, &y, &z);
scanf(" %c %c", &status1, &status2);
if (status1 != status2) {
 if ((status1 == 'Y' && status2 == 'n') || (status1 == 'n' && status2 == 'Y')) {
   sum = x+y;
 }else if (( status1 == 'Y' && status2 == 'N') || (status1 == 'N' &&  status2 == 'Y')) {
   sum = (int) ceil((float)(x+y)/z);
 }else if ((status1 == 'N' && status2 == 'y') ||  (status1 == 'y' && status2 == 'N')) {
   sum = (int) ceil((float)x/z);
 }else if ((status1 = 'N' && status2 == 'n') || (status1 == 'n' && status2 == 'N')) {
   sum = x;
 }else {
    if (status1 == 'Y') {
        if (status2 == 'Y') {
          sum = x+y;
        }else if (status2 == 'y'){
          sum = (int) ceil((float)(x+y)/z);
        }
      }else if (status1 == 'N'){
        if ( status1 == 'N'){
          sum = x;
        }else if ( status2 == 'n'){
          sum = x;
        }
      }else if (status1 == 'y'){
        if (status2 == 'y'){
          sum = (int) ceil((float)x/z);
        }else if (status2 == 'Y'){
          sum = (int) ceil((float)x/z); 
        }
      }else if (status1 == 'n'){
        if (status2 == 'n'){
          sum = x;
        }else if (status2 == 'N'){
          sum = x;
        }
      }




}

 printf("%d", sum);


}
return 0;
}
