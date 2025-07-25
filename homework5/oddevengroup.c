#include <stdio.h>
#include <stdlib.h>

int main() {
  int capacity = 4;
  int index = 0;
  int *arr = malloc(sizeof(int) * capacity);
  int num;


  while (scanf("%d", &num) == 1 && num != -1){
    capacity += 4;
    arr = realloc(arr, sizeof(int) * capacity);
    arr[index++] = num;

  }

  int index_odd = 0;
  int index_even = 0;
  int new_arr[index];

  for (int i = 0; i<index;i++){
      if (arr[i] % 2 != 0 ) {
       new_arr[index_odd++] = arr[i];
      }
  }
  for (int i = 0; i<index;i++){
      if (arr[i] % 2 == 0 ) {
        new_arr[index_odd + index_even] = arr[i];
        index_even++;
      }

  }

  for (int i = 0; i<index;i++) {
      printf("%d ",new_arr[i]);


  }

}
