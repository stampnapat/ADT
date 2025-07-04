#include <stdio.h>
#include <math.h>

int main() {
  int n;
  char compass = 'E';
  scanf("%d",&n);
  char arr[n];
  int x = 0, y = 0;
  scanf("%s",arr);
  for (int i =0;i<n;i++){
    if (arr[i] == 'F'){
        if (compass == 'E'){
            x += 1 ;
        }else if (compass == 'W') {
            x -= 1;
        }else if (compass == 'N') {
            y += 1;
        }else if (compass == 'S') {
            y -= 1;
        }
    }else if (arr[i] == 'R'){
          if (compass == 'E') compass = 'S';
          else if (compass == 'S') compass = 'W';
          else if (compass == 'W') compass = 'N';
          else if (compass == 'N') compass = 'E';
    }else if (arr[i] == 'L'){
          if (compass == 'E') compass = 'N';
          else if (compass == 'N') compass = 'W';
          else if (compass == 'W') compass = 'S';
          else if (compass == 'S') compass = 'E';
    }}
  printf("%.4lf", sqrt((x*x)+(y*y)));
  return 0;
}  
