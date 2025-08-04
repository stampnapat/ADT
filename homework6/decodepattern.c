#include <stdio.h>

int main() {
  int n;
  scanf("%d", &n);

  char arr[n+1];

  scanf("%s", arr);

  int stack[n+1];
  int top=0;
  int number = 1;
  for (int i = 0; i<=n;i++){
    stack[top++] = number;
    number++;

    if (i==n|| arr[i] == 'I'){
      while (top >0){
        top -= 1;
        printf("%d ", stack[top]);
      }
    }
  }


}
