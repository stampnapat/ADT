#include <stdio.h>
#include <stdlib.h>

int main() {
  int capacity = 4;
  int num;
  int index = 0;
  int *arr = malloc(sizeof(int) *capacity);
  while (scanf("%d", &num) == 1 && num != -1) {
  capacity += 4;
  arr = realloc(arr, sizeof(int) * capacity);
  arr[index++] = num;

  }
  int reverse_count;
  scanf("%d", &reverse_count);


  int check = index;
  int count_index = 0;




  while (index > count_index) {
    int reverse = (index - count_index >= reverse_count) ? reverse_count : index - count_index;
     if (reverse < reverse_count) {
        for (int i = 0 ; i<reverse;i++){
            printf("%d ", arr[i+count_index]);
        }
      }
    else {
      for (int i = reverse -1 ; i>= 0; i--){
            printf("%d ", arr[i+count_index]);
       }
}
        count_index += reverse;
       // check -= reverse;





}
}
